#include "data_storage.h"

// Values for L-R cues experiment

const int conditionOrders[5][NUM_CONDITIONS] = {
	{ 45, 59, 34, 29, 55, 42, 31, 51, 11, 23, 64, 12,  7, 69, 16, 60, 37,  2, 39, 50,  6,  9, 18, 61,  8, 14, 63, 35, 56, 36, 17, 38, 44, 65, 26, 13, 52, 72, 15, 67, 19, 33, 70, 43, 32, 57, 46, 10, 27,  1, 53, 20, 21,  4,  3, 22, 40, 71, 49, 24,  5, 66, 68, 47, 58, 28, 62, 25, 30, 54, 41, 48 },
	{ 15, 42, 16, 31, 59, 55, 24, 45,  2, 34, 12, 64, 25, 37, 69,  1, 60, 39, 51, 50, 17, 32,  4, 61, 29, 63, 35, 72, 56, 10, 36, 38, 21,  8, 13, 65, 33, 52, 30, 14, 67,  5, 70, 43, 46, 57,  6, 27, 44,  9, 11, 53,  3, 28, 18, 20, 41, 23, 40,  7, 71, 58, 66, 68, 48, 19, 62, 49, 54, 22, 47, 26 },
	{ 70, 41, 32,  9, 59, 45, 31, 20,  4, 34, 51, 37, 64,  8, 69, 13, 60, 24,  2,  3, 55, 39, 21, 44, 47, 35, 63, 25, 72, 56, 16, 61, 50, 18, 52, 42, 38, 33, 23, 67, 57, 29, 14,  1, 65, 30, 53, 43, 22, 28, 15, 11, 40, 26,  7,  6, 66, 12,  5, 58, 62, 17, 68, 19, 54, 36, 10, 49, 71, 27, 46, 48 },
    {  4, 70, 15, 14, 51, 34, 18,  6, 72, 44, 25, 41,  3, 32, 64, 55, 60,  1, 11, 37, 35, 69, 71, 17, 39, 48, 52,  9, 56, 63, 22, 33, 61, 36, 38, 45, 29, 43,  5, 50, 16, 67, 31, 42, 21, 65, 23,  8, 24, 53,  2, 19, 40, 57,  7, 62, 13, 26, 20, 66, 58, 10, 47, 28, 68, 49, 54, 30, 59, 12, 27, 46 },
    { 51, 11, 70, 25, 72,  8, 44, 29, 22,  6, 52, 69, 12, 55,  2, 60, 18, 34, 37, 15, 41, 63, 17, 71,  9, 56, 48, 50, 35, 42, 61, 43, 39, 31, 45, 36, 14, 38, 32, 27, 67, 21, 65,  1, 53, 13, 49, 26,  5, 57, 33,  4, 40, 19, 62, 10, 47, 66, 58, 30, 16, 64,  3, 24, 54,  7, 68, 20, 23, 59, 46, 28 }

};

const int orders[2][5]{
	{ 0, 4, 2, 1, 3 },
	{ 1, 0, 3, 4, 2 } 
};


//int cues[4][TRIALS_MAX] = {
//{ 1, 17, 8, 13, 10, 16, 2, 15, 23, 3, 19, 21, 7, 18, 4, 9, 12, 5, 14, 24, 20, 11, 6, 22 },
//{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 },
//{ 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23, 6, 12, 18, 24 },
//{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 },
// };


// each participant number receives a designated condition order (a row from "cues")
const int orderVec[20] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

/*

selectedOrder = orders[orderVec[particpantNum]]
int cues[TRIALS_MAX];
for(set = 1:10)
row = orders[orderVec[praticipantNum]][set]
for(col; = 0, col< NUM_CONDITIONS; col++)
cues[24*i+j]= conditionOrders[row][col];


*/
