// ============================================================================
// Week 4 Live Coding: Music Streaming Service
// 
// Building on Week 3's pointer fundamentals, we'll practice:
// - More complex pointer chains
// - Multiple pointer relationships
// - Arrays of pointers (filtering, collecting)
// - Double pointers for sorting and swapping
// - Defensive programming with nullptr checks
//
// This uses a MUSIC STREAMING system so you can learn the patterns
// that apply directly to your Guest Management assignment!
// ============================================================================

#include <iostream>
#include <cstring>
using namespace std;

// ============================================================================
// DATA STRUCTURES
// Notice how these mirror your assignment's structure!
// ============================================================================

struct Artist {
    int artistId;
    char name[50];
    char genre[30];
    int monthlyListeners;
    bool isVerified;
};

struct Song {
    int songId;
    char title[100];
    int durationSeconds;
    int playCount;
    Artist* artist;         // POINTER to the artist (like Room->currentGuest)
};

struct Playlist {
    int playlistId;
    char name[50];
    Song* songs[50];        // Array of POINTERS to songs
    int songCount;
    bool isPublic;
};

struct User {
    int userId;
    char username[30];
    int totalMinutesListened;
    bool isPremium;
};

struct StreamRecord {
    int recordId;
    User* user;             // POINTER to user (like Reservation->guest)
    Song* song;             // POINTER to song (like Reservation->room)
    int timestamp;
    bool completed;         // Did they finish the song?
};

// ============================================================================
// PART A: WARM-UP - Basic Pointer Operations (Review)
// These reinforce Week 3 fundamentals
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE A1: Find and return pointer
// Pattern: Loop, compare, return address or nullptr
// 
// This is the SAME pattern as findGuestById in your assignment!
// ----------------------------------------------------------------------------
Artist* findArtistById(Artist artists[], int size, int artistId) {
    // TODO: Find artist with matching ID, return pointer or nullptr
    
    return nullptr;
}

void exerciseA1() {
    cout << "=== Exercise A1: Find and Return Pointer ===" << endl;
    
    Artist artists[3] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Drake", "Hip-Hop", 67000000, true},
        {3, "Local Band", "Rock", 5000, false}
    };
    
    // Test: Find existing artist
    Artist* found = findArtistById(artists, 3, 2);
    if (found != nullptr) {
        cout << "Found: " << found->name << endl;  // Should print "Drake"
    }
    
    // Test: Artist not found
    Artist* notFound = findArtistById(artists, 3, 999);
    cout << "Search for 999: " << (notFound == nullptr ? "Not found" : "ERROR") << endl;
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE A2: Find by string comparison
// Pattern: Same as A1, but use strcmp for strings
//
// This is the SAME pattern as findGuestByName in your assignment!
// ----------------------------------------------------------------------------
Artist* findArtistByName(Artist artists[], int size, const char* name) {
    // TODO: Find artist with matching name using strcmp
    
    return nullptr;
}

void exerciseA2() {
    cout << "=== Exercise A2: Find by String ===" << endl;
    
    Artist artists[3] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Drake", "Hip-Hop", 67000000, true},
        {3, "Local Band", "Rock", 5000, false}
    };
    
    Artist* taylor = findArtistByName(artists, 3, "Taylor Swift");
    if (taylor != nullptr) {
        cout << "Found Taylor! Genre: " << taylor->genre << endl;
    }
    
    Artist* unknown = findArtistByName(artists, 3, "Unknown Artist");
    cout << "Unknown Artist: " << (unknown == nullptr ? "Not found" : "ERROR") << endl;
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE A3: Count with condition
// Pattern: Loop, check condition, increment counter
//
// This is the SAME pattern as countCheckedInGuests!
// ----------------------------------------------------------------------------
int countVerifiedArtists(const Artist artists[], int size) {
    // TODO: Count artists where isVerified is true
    
    return 0;
}

int countPremiumUsers(const User users[], int size) {
    // TODO: Count users where isPremium is true
    
    return 0;
}

void exerciseA3() {
    cout << "=== Exercise A3: Count with Condition ===" << endl;
    
    Artist artists[4] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Drake", "Hip-Hop", 67000000, true},
        {3, "Local Band", "Rock", 5000, false},
        {4, "Bedroom Producer", "Electronic", 1000, false}
    };
    
    cout << "Verified artists: " << countVerifiedArtists(artists, 4) << endl;  // Should be 2
    
    User users[3] = {
        {1, "alice", 5000, true},
        {2, "bob", 200, false},
        {3, "charlie", 15000, true}
    };
    
    cout << "Premium users: " << countPremiumUsers(users, 3) << endl;  // Should be 2
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE A4: Find maximum
// Pattern: Track pointer to best, update when finding better
//
// This is the SAME pattern as findTopLoyaltyMember!
// ----------------------------------------------------------------------------
Artist* findMostPopularArtist(Artist artists[], int size) {
    // TODO: Find artist with highest monthlyListeners
    // Handle edge case: return nullptr if size is 0
    
    return nullptr;
}

void exerciseA4() {
    cout << "=== Exercise A4: Find Maximum ===" << endl;
    
    Artist artists[4] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Drake", "Hip-Hop", 67000000, true},
        {3, "Bad Bunny", "Latin", 78000000, true},
        {4, "The Weeknd", "R&B", 75000000, true}
    };
    
    Artist* mostPopular = findMostPopularArtist(artists, 4);
    if (mostPopular != nullptr) {
        cout << "Most popular: " << mostPopular->name 
             << " (" << mostPopular->monthlyListeners << " listeners)" << endl;
    }
    
    // Edge case: empty array
    Artist* empty = findMostPopularArtist(artists, 0);
    cout << "Empty array result: " << (empty == nullptr ? "nullptr (correct!)" : "ERROR") << endl;
    
    cout << endl;
}

// ============================================================================
// PART B: Connecting Objects with Pointers
// This is like Room->currentGuest or Reservation->guest
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE B1: Set up a pointer connection
// Pattern: Check nulls, check preconditions, assign pointer, update state
//
// This is the SAME pattern as checkGuestIntoRoom!
// ----------------------------------------------------------------------------
bool assignArtistToSong(Song* song, Artist* artist) {
    // TODO: 
    // 1. Check that both song and artist are not nullptr
    // 2. Check that song doesn't already have an artist (song->artist == nullptr)
    // 3. Set song->artist = artist
    // 4. Return true if successful, false otherwise
    
    return false;
}

void exerciseB1() {
    cout << "=== Exercise B1: Connect Objects ===" << endl;
    
    Artist taylor = {1, "Taylor Swift", "Pop", 82000000, true};
    Song song1 = {101, "Anti-Hero", 200, 0, nullptr};  // No artist yet
    Song song2 = {102, "Shake It Off", 219, 1000000, &taylor};  // Already has artist
    
    // Should succeed - song has no artist
    if (assignArtistToSong(&song1, &taylor)) {
        cout << "Assigned Taylor to Anti-Hero: " << song1.artist->name << endl;
    }
    
    // Should fail - song already has an artist
    Artist drake = {2, "Drake", "Hip-Hop", 67000000, true};
    if (!assignArtistToSong(&song2, &drake)) {
        cout << "Correctly rejected - Shake It Off already has artist: " 
             << song2.artist->name << endl;
    }
    
    // Should fail - nullptr check
    if (!assignArtistToSong(nullptr, &taylor)) {
        cout << "Correctly rejected nullptr song" << endl;
    }
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE B2: Remove connection and return the removed pointer
// Pattern: Save pointer, clear connection, update state, return saved
//
// This is the SAME pattern as checkGuestOutOfRoom!
// ----------------------------------------------------------------------------
Artist* removeArtistFromSong(Song* song) {
    // TODO:
    // 1. Check that song is not nullptr - return nullptr if it is
    // 2. Save song->artist to a temporary variable
    // 3. Set song->artist = nullptr
    // 4. Return the saved pointer (might be nullptr if song had no artist)
    
    return nullptr;
}

void exerciseB2() {
    cout << "=== Exercise B2: Remove and Return Pointer ===" << endl;
    
    Artist taylor = {1, "Taylor Swift", "Pop", 82000000, true};
    Song song = {101, "Anti-Hero", 200, 500000, &taylor};
    
    cout << "Before removal: " << song.artist->name << endl;
    
    Artist* removed = removeArtistFromSong(&song);
    
    cout << "Removed artist: " << removed->name << endl;
    cout << "Song's artist now: " << (song.artist == nullptr ? "nullptr" : "ERROR") << endl;
    
    // Try removing from song with no artist
    Artist* removedAgain = removeArtistFromSong(&song);
    cout << "Remove again: " << (removedAgain == nullptr ? "nullptr (correct)" : "ERROR") << endl;
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE B3: Find object by its pointer relationship
// Pattern: Loop, compare pointers, return address
//
// This is the SAME pattern as findGuestRoom!
// ----------------------------------------------------------------------------
Song* findSongByArtist(Song songs[], int size, const Artist* artist) {
    // TODO: Find the first song where song.artist == artist (pointer comparison)
    // Return pointer to song, or nullptr if not found
    
    return nullptr;
}

void exerciseB3() {
    cout << "=== Exercise B3: Find by Pointer Relationship ===" << endl;
    
    Artist artists[2] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Drake", "Hip-Hop", 67000000, true}
    };
    
    Song songs[3] = {
        {101, "Anti-Hero", 200, 500000, &artists[0]},
        {102, "God's Plan", 198, 2000000, &artists[1]},
        {103, "Blank Space", 231, 3000000, &artists[0]}
    };
    
    // Find Taylor's song (should find first one - Anti-Hero)
    Song* taylorSong = findSongByArtist(songs, 3, &artists[0]);
    if (taylorSong != nullptr) {
        cout << "Found Taylor's song: " << taylorSong->title << endl;
    }
    
    // Search for artist not in any song
    Artist unknown = {99, "Unknown", "Jazz", 100, false};
    Song* notFound = findSongByArtist(songs, 3, &unknown);
    cout << "Unknown artist's song: " << (notFound == nullptr ? "Not found" : "ERROR") << endl;
    
    cout << endl;
}

// ============================================================================
// PART C: Arrays of Pointers (Filtering/Collecting)
// This is like getVacantRooms or findGuestReservations
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE C1: Fill array with pointers matching a condition
// Pattern: Loop, check condition, store address, increment counter
//
// This is the SAME pattern as getVacantRooms!
// ----------------------------------------------------------------------------
int getVerifiedArtists(Artist artists[], int size, Artist* verified[]) {
    // TODO: Fill verified[] with pointers to artists where isVerified == true
    // Return count of verified artists found
    
    return 0;
}

void exerciseC1() {
    cout << "=== Exercise C1: Collect Matching Pointers ===" << endl;
    
    Artist artists[5] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Local Band", "Rock", 5000, false},
        {3, "Drake", "Hip-Hop", 67000000, true},
        {4, "Bedroom Producer", "Electronic", 1000, false},
        {5, "Bad Bunny", "Latin", 78000000, true}
    };
    
    Artist* verified[5];
    int count = getVerifiedArtists(artists, 5, verified);
    
    cout << "Verified artists (" << count << "):" << endl;
    for (int i = 0; i < count; i++) {
        cout << "  - " << verified[i]->name << endl;
    }
    // Should print: Taylor Swift, Drake, Bad Bunny
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE C2: Filter by range (multiple conditions)
// Pattern: Same as C1, but check range
//
// This is the SAME pattern as findGuestsInPointsRange!
// ----------------------------------------------------------------------------
int getArtistsInListenerRange(Artist artists[], int size, 
                               int minListeners, int maxListeners,
                               Artist* result[]) {
    // TODO: Find artists with monthlyListeners between min and max (inclusive)
    // Store pointers in result[], return count
    
    return 0;
}

void exerciseC2() {
    cout << "=== Exercise C2: Filter by Range ===" << endl;
    
    Artist artists[5] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Mid Artist", "Rock", 5000000, true},
        {3, "Drake", "Hip-Hop", 67000000, true},
        {4, "Small Artist", "Jazz", 100000, false},
        {5, "Rising Star", "Pop", 2000000, true}
    };
    
    Artist* midTier[5];
    int count = getArtistsInListenerRange(artists, 5, 1000000, 10000000, midTier);
    
    cout << "Mid-tier artists (1M-10M listeners): " << count << endl;
    for (int i = 0; i < count; i++) {
        cout << "  - " << midTier[i]->name 
             << " (" << midTier[i]->monthlyListeners << ")" << endl;
    }
    // Should print: Mid Artist (5M), Rising Star (2M)
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE C3: Find by pointer match and additional condition
// Pattern: Check pointer equality AND another condition
//
// This is the SAME pattern as findGuestReservations!
// ----------------------------------------------------------------------------
int getCompletedStreamsForUser(StreamRecord records[], int size,
                                const User* user, StreamRecord* result[]) {
    // TODO: Find all records where:
    //   - records[i].user == user (pointer comparison)
    //   - records[i].completed == true
    // Store pointers in result[], return count
    
    return 0;
}

void exerciseC3() {
    cout << "=== Exercise C3: Filter by Pointer + Condition ===" << endl;
    
    User users[2] = {
        {1, "alice", 5000, true},
        {2, "bob", 200, false}
    };
    
    Artist taylor = {1, "Taylor Swift", "Pop", 82000000, true};
    Song songs[3] = {
        {101, "Anti-Hero", 200, 0, &taylor},
        {102, "Blank Space", 231, 0, &taylor},
        {103, "Shake It Off", 219, 0, &taylor}
    };
    
    StreamRecord records[5] = {
        {1, &users[0], &songs[0], 1000, true},   // Alice completed
        {2, &users[0], &songs[1], 1001, false},  // Alice didn't complete
        {3, &users[1], &songs[0], 1002, true},   // Bob completed
        {4, &users[0], &songs[2], 1003, true},   // Alice completed
        {5, &users[0], &songs[0], 1004, true}    // Alice completed (replay)
    };
    
    StreamRecord* aliceCompleted[5];
    int count = getCompletedStreamsForUser(records, 5, &users[0], aliceCompleted);
    
    cout << "Alice's completed streams: " << count << endl;
    for (int i = 0; i < count; i++) {
        cout << "  - " << aliceCompleted[i]->song->title << endl;
    }
    // Should print 3 songs: Anti-Hero, Shake It Off, Anti-Hero (replay)
    
    cout << endl;
}

// ============================================================================
// PART D: Pointer Chains and Calculations
// This is like calculateReservationCost and calculateTotalRevenue
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE D1: Access data through pointer chain
// Pattern: Check each pointer in chain, then access the data
//
// This is the SAME pattern as calculateReservationCost!
// ----------------------------------------------------------------------------
int getStreamDuration(const StreamRecord* record) {
    // TODO: Return the duration of the streamed song
    // Access: record->song->durationSeconds
    // Check that record is not nullptr
    // Check that record->song is not nullptr
    // Return 0 if any pointer is null
    
    return 0;
}

const char* getStreamArtistName(const StreamRecord* record) {
    // TODO: Return the name of the artist of the streamed song
    // Access: record->song->artist->name
    // Must check: record, record->song, record->song->artist
    // Return "Unknown" if any pointer is null
    
    return "Unknown";
}

void exerciseD1() {
    cout << "=== Exercise D1: Pointer Chains ===" << endl;
    
    User alice = {1, "alice", 5000, true};
    Artist taylor = {1, "Taylor Swift", "Pop", 82000000, true};
    Song song = {101, "Anti-Hero", 200, 500000, &taylor};
    StreamRecord record = {1, &alice, &song, 1000, true};
    
    cout << "Stream duration: " << getStreamDuration(&record) << " seconds" << endl;
    cout << "Artist name: " << getStreamArtistName(&record) << endl;
    
    // Test with broken chain
    Song songNoArtist = {102, "Mystery", 180, 0, nullptr};
    StreamRecord brokenRecord = {2, &alice, &songNoArtist, 1001, false};
    cout << "Broken chain artist: " << getStreamArtistName(&brokenRecord) << endl;
    
    // Test with nullptr
    cout << "Null record duration: " << getStreamDuration(nullptr) << endl;
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE D2: Aggregate calculation using helper function
// Pattern: Loop, check condition, call helper, accumulate
//
// This is the SAME pattern as calculateTotalRevenue!
// ----------------------------------------------------------------------------
int calculateTotalListenTime(const StreamRecord records[], int size) {
    // TODO: Sum up duration of all COMPLETED streams
    // Use getStreamDuration for each completed record
    // Remember: pass address with &records[i]
    
    return 0;
}

void exerciseD2() {
    cout << "=== Exercise D2: Aggregate with Helper ===" << endl;
    
    User alice = {1, "alice", 5000, true};
    Artist taylor = {1, "Taylor Swift", "Pop", 82000000, true};
    
    Song songs[3] = {
        {101, "Anti-Hero", 200, 0, &taylor},      // 200 seconds
        {102, "Blank Space", 231, 0, &taylor},    // 231 seconds  
        {103, "Shake It Off", 219, 0, &taylor}    // 219 seconds
    };
    
    StreamRecord records[4] = {
        {1, &alice, &songs[0], 1000, true},   // Completed: 200
        {2, &alice, &songs[1], 1001, false},  // Not completed
        {3, &alice, &songs[2], 1002, true},   // Completed: 219
        {4, &alice, &songs[0], 1003, true}    // Completed: 200
    };
    
    int totalTime = calculateTotalListenTime(records, 4);
    cout << "Total listen time: " << totalTime << " seconds" << endl;
    // Should be 200 + 219 + 200 = 619 seconds
    
    cout << endl;
}

// ============================================================================
// PART E: Double Pointers (Swapping and Sorting)
// This is like swapGuestPointers and sortGuestsByLoyalty
// ============================================================================

// ----------------------------------------------------------------------------
// EXERCISE E1: Swap pointers using double pointers
// Pattern: Use temp variable, swap via dereferencing
//
// This is the SAME pattern as swapGuestPointers!
// ----------------------------------------------------------------------------
void swapArtistPointers(Artist** a1, Artist** a2) {
    // TODO: Swap the Artist* values that a1 and a2 point to
    // *a1 is the Artist* that a1 points to
    // Use standard swap: temp = *a1; *a1 = *a2; *a2 = temp;
    
}

void exerciseE1() {
    cout << "=== Exercise E1: Swap Pointers ===" << endl;
    
    Artist taylor = {1, "Taylor Swift", "Pop", 82000000, true};
    Artist drake = {2, "Drake", "Hip-Hop", 67000000, true};
    
    Artist* ptr1 = &taylor;
    Artist* ptr2 = &drake;
    
    cout << "Before swap:" << endl;
    cout << "  ptr1 -> " << ptr1->name << endl;
    cout << "  ptr2 -> " << ptr2->name << endl;
    
    swapArtistPointers(&ptr1, &ptr2);
    
    cout << "After swap:" << endl;
    cout << "  ptr1 -> " << ptr1->name << endl;
    cout << "  ptr2 -> " << ptr2->name << endl;
    
    // Verify original artists unchanged
    cout << "Original taylor: " << taylor.name << endl;
    cout << "Original drake: " << drake.name << endl;
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// EXERCISE E2: Sort array of pointers
// Pattern: Bubble sort with pointer comparison and swap function
//
// This is the SAME pattern as sortGuestsByLoyalty!
// ----------------------------------------------------------------------------
void sortArtistsByListeners(Artist* artistPtrs[], int size) {
    // TODO: Sort by monthlyListeners in DESCENDING order (highest first)
    // Use bubble sort:
    //   for i from 0 to size-1
    //     for j from 0 to size-1-i
    //       if artistPtrs[j]->monthlyListeners < artistPtrs[j+1]->monthlyListeners
    //         swapArtistPointers(&artistPtrs[j], &artistPtrs[j+1])
    
}

void exerciseE2() {
    cout << "=== Exercise E2: Sort Pointer Array ===" << endl;
    
    Artist artists[5] = {
        {1, "Taylor Swift", "Pop", 82000000, true},
        {2, "Local Band", "Rock", 5000, false},
        {3, "Drake", "Hip-Hop", 67000000, true},
        {4, "Rising Star", "Pop", 2000000, true},
        {5, "Bad Bunny", "Latin", 78000000, true}
    };
    
    // Create array of pointers
    Artist* ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = &artists[i];
    }
    
    cout << "Before sorting:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  " << ptrs[i]->name << ": " << ptrs[i]->monthlyListeners << endl;
    }
    
    sortArtistsByListeners(ptrs, 5);
    
    cout << "After sorting (descending by listeners):" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  " << ptrs[i]->name << ": " << ptrs[i]->monthlyListeners << endl;
    }
    // Expected: Taylor(82M), Bad Bunny(78M), Drake(67M), Rising Star(2M), Local Band(5K)
    
    // Verify original array unchanged
    cout << "Original array order preserved:" << endl;
    cout << "  artists[0] = " << artists[0].name << endl;
    cout << "  artists[1] = " << artists[1].name << endl;
    
    cout << endl;
}

// ============================================================================
// PART F: Putting It All Together - Mini Challenge
// Combine multiple pointer techniques
// ============================================================================

// ----------------------------------------------------------------------------
// CHALLENGE: Complex query combining multiple techniques
// Find top artist among verified artists with listeners in a range
// ----------------------------------------------------------------------------
Artist* findTopVerifiedArtistInRange(Artist artists[], int size,
                                      int minListeners, int maxListeners) {
    // TODO: 
    // 1. Find all artists in the listener range (use your range pattern)
    // 2. Among those, find only verified artists
    // 3. Return pointer to the one with the most listeners
    // 4. Return nullptr if no artists match both criteria
    //
    // Hint: You can do this in one pass through the array!
    // Track best verified artist in range as you go.
    
    return nullptr;
}

void exerciseF() {
    cout << "=== Challenge: Complex Query ===" << endl;
    
    Artist artists[6] = {
        {1, "Taylor Swift", "Pop", 82000000, true},      // Verified, out of range (too high)
        {2, "Mid Verified", "Rock", 5000000, true},      // Verified, in range
        {3, "Mid Unverified", "Jazz", 7000000, false},   // Not verified
        {4, "Small Verified", "Pop", 1000000, true},     // Verified, in range
        {5, "Rising Star", "Hip-Hop", 3000000, true},    // Verified, in range
        {6, "Tiny Artist", "Folk", 50000, true}          // Verified, out of range (too low)
    };
    
    // Find top verified artist between 500K and 10M listeners
    Artist* top = findTopVerifiedArtistInRange(artists, 6, 500000, 10000000);
    
    if (top != nullptr) {
        cout << "Top verified artist in range: " << top->name 
             << " (" << top->monthlyListeners << " listeners)" << endl;
        // Should be "Mid Verified" with 5M listeners
    } else {
        cout << "No matching artists found" << endl;
    }
    
    // Test with range that has no verified artists
    Artist* none = findTopVerifiedArtistInRange(artists, 6, 100000000, 200000000);
    cout << "Empty range result: " << (none == nullptr ? "nullptr (correct)" : "ERROR") << endl;
    
    cout << endl;
}

// ============================================================================
// MAIN - Run exercises progressively
// ============================================================================

int main() {
    cout << "Week 4: Advanced Pointer Practice" << endl;
    cout << "==================================" << endl;
    cout << "Complete each exercise to prepare for your assignment!" << endl;
    cout << endl;
    
    // PART A: Review fundamentals
    // exerciseA1();  // Find and return pointer
    // exerciseA2();  // Find by string
    // exerciseA3();  // Count with condition
    // exerciseA4();  // Find maximum
    
    // PART B: Connecting objects
    // exerciseB1();  // Set up connection
    // exerciseB2();  // Remove and return
    // exerciseB3();  // Find by relationship
    
    // PART C: Arrays of pointers
    // exerciseC1();  // Collect matching
    // exerciseC2();  // Filter by range
    // exerciseC3();  // Filter by pointer + condition
    
    // PART D: Pointer chains
    // exerciseD1();  // Access through chain
    // exerciseD2();  // Aggregate calculation
    
    // PART E: Double pointers
    // exerciseE1();  // Swap pointers
    // exerciseE2();  // Sort pointer array
    
    // PART F: Challenge
    // exerciseF();   // Complex query
    
    cout << "========================================" << endl;
    cout << "Mapping to Your Assignment:" << endl;
    cout << "========================================" << endl;
    cout << "A1 findArtistById        -> findGuestById" << endl;
    cout << "A2 findArtistByName      -> findGuestByName" << endl;
    cout << "A3 countVerifiedArtists  -> countCheckedInGuests" << endl;
    cout << "A4 findMostPopular       -> findTopLoyaltyMember" << endl;
    cout << "B1 assignArtistToSong    -> checkGuestIntoRoom" << endl;
    cout << "B2 removeArtistFromSong  -> checkGuestOutOfRoom" << endl;
    cout << "B3 findSongByArtist      -> findGuestRoom" << endl;
    cout << "C1 getVerifiedArtists    -> getVacantRooms" << endl;
    cout << "C2 getArtistsInRange     -> findGuestsInPointsRange" << endl;
    cout << "C3 getCompletedStreams   -> findGuestReservations" << endl;
    cout << "D1 getStreamDuration     -> calculateReservationCost" << endl;
    cout << "D2 calculateTotalTime    -> calculateTotalRevenue" << endl;
    cout << "E1 swapArtistPointers    -> swapGuestPointers" << endl;
    cout << "E2 sortByListeners       -> sortGuestsByLoyalty" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
