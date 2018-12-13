#ifndef DATA_STORAGE
#define DATA_STORAGE

// Values for L-R cues experiment

// STATES
#define SETUP 0
#define BETWEEN_TRIALS 1
#define WAITING_FOR_INPUT 2
#define WAITING_FOR_ENTER 3

// break points
#define BREAK1 120
#define BREAK2 240


// CONDITION ORDERS
#define TRIALS_MAX 360
#define NUM_CONDITIONS 72
extern const int orderVec[20];
extern const int orders[2][5];
extern const int conditionOrders[5][NUM_CONDITIONS];
#endif
