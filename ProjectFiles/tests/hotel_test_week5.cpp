// ============================================================================
// Hotel Management System - Week 5 Test Suite
// Tests for: Person (base), Room (base), Payment (base) classes
// 
// Build: g++ -std=c++17 base_classes.cpp hotel_classes.cpp system_classes.cpp hotel_test_week5.cpp -lgtest -lgtest_main -pthread -o hotel_test_week5
// Run: ./hotel_test_week5
// ============================================================================

#include <gtest/gtest.h>
#include <cstring>
#include "hotel_classes.h"  // Includes base_classes.h

// ============================================================================
// PERSON CLASS TESTS
// ============================================================================

class PersonTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
};

// --- Constructor Tests ---

TEST_F(PersonTest, DefaultConstructor) {
    Person p;
    EXPECT_EQ(p.getId(), 0);
    EXPECT_STREQ(p.getName(), "");
    EXPECT_STREQ(p.getPhone(), "");
    EXPECT_STREQ(p.getEmail(), "");
}

TEST_F(PersonTest, ParameterizedConstructor) {
    Person p(101, "John Doe", "555-1234", "john@email.com");
    EXPECT_EQ(p.getId(), 101);
    EXPECT_STREQ(p.getName(), "John Doe");
    EXPECT_STREQ(p.getPhone(), "555-1234");
    EXPECT_STREQ(p.getEmail(), "john@email.com");
}

TEST_F(PersonTest, ConstructorWithEmptyStrings) {
    Person p(1, "", "", "");
    EXPECT_EQ(p.getId(), 1);
    EXPECT_STREQ(p.getName(), "");
    EXPECT_STREQ(p.getPhone(), "");
    EXPECT_STREQ(p.getEmail(), "");
}

// --- Getter Tests ---

TEST_F(PersonTest, GettersReturnCorrectValues) {
    Person p(42, "Alice Smith", "555-9999", "alice@test.com");
    EXPECT_EQ(p.getId(), 42);
    EXPECT_STREQ(p.getName(), "Alice Smith");
    EXPECT_STREQ(p.getPhone(), "555-9999");
    EXPECT_STREQ(p.getEmail(), "alice@test.com");
}

// --- Setter Tests ---

TEST_F(PersonTest, SetName) {
    Person p(1, "Original", "555-0000", "orig@test.com");
    p.setName("New Name");
    EXPECT_STREQ(p.getName(), "New Name");
}

TEST_F(PersonTest, SetPhone) {
    Person p(1, "Test", "555-0000", "test@test.com");
    p.setPhone("999-8888");
    EXPECT_STREQ(p.getPhone(), "999-8888");
}

TEST_F(PersonTest, SetEmail) {
    Person p(1, "Test", "555-0000", "old@test.com");
    p.setEmail("new@email.com");
    EXPECT_STREQ(p.getEmail(), "new@email.com");
}

TEST_F(PersonTest, SettersDoNotAffectOtherFields) {
    Person p(100, "Name", "555-1111", "email@test.com");
    p.setName("Changed");
    EXPECT_EQ(p.getId(), 100);  // ID unchanged
    EXPECT_STREQ(p.getPhone(), "555-1111");  // Phone unchanged
    EXPECT_STREQ(p.getEmail(), "email@test.com");  // Email unchanged
}

// ============================================================================
// PAYMENT BASE CLASS TESTS
// Payment is abstract, so test through minimal concrete implementation
// ============================================================================

class TestPayment : public Payment {
private:
    bool shouldProcess;
public:
    TestPayment() : Payment(), shouldProcess(true) {}
    TestPayment(int id, double amt) : Payment(id, amt), shouldProcess(true) {}
    
    void setShouldProcess(bool val) { shouldProcess = val; }
    
    // Implement pure virtual functions minimally for testing
    bool processPayment() override {
        if (shouldProcess) {
            return true;
        }
        return false;
    }
    
    bool refund() override { return true; }
    const char* getPaymentType() const override { return "Test"; }
    void display() const override {}
};

class PaymentBaseTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(PaymentBaseTest, DefaultConstructor) {
    TestPayment payment;
    EXPECT_EQ(payment.getPaymentId(), 0);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 0.0);
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(PaymentBaseTest, ParameterizedConstructor) {
    TestPayment payment(123, 250.50);
    EXPECT_EQ(payment.getPaymentId(), 123);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 250.50);
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(PaymentBaseTest, GettersReturnCorrectValues) {
    TestPayment payment(42, 99.99);
    EXPECT_EQ(payment.getPaymentId(), 42);
    EXPECT_DOUBLE_EQ(payment.getAmount(), 99.99);
}

TEST_F(PaymentBaseTest, InitiallyNotProcessed) {
    TestPayment payment(1, 100.0);
    EXPECT_FALSE(payment.getIsProcessed());
}

TEST_F(PaymentBaseTest, DefaultTransactionFeeIsZero) {
    TestPayment payment(1, 100.0);
    EXPECT_DOUBLE_EQ(payment.getTransactionFee(), 0.0);
}

TEST_F(PaymentBaseTest, TimestampFieldExists) {
    TestPayment payment(1, 100.0);
    EXPECT_NE(payment.getTimestamp(), nullptr);
}

TEST_F(PaymentBaseTest, ProcessPaymentCanSucceed) {
    TestPayment payment(1, 100.0);
    payment.setShouldProcess(true);
    bool result = payment.processPayment();
    EXPECT_TRUE(result);
}

TEST_F(PaymentBaseTest, ProcessPaymentCanFail) {
    TestPayment payment(1, 100.0);
    payment.setShouldProcess(false);
    bool result = payment.processPayment();
    EXPECT_FALSE(result);
}
