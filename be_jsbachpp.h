#ifndef BE_JSBACHPP
#define BE_JSBACHPP

void initTracks();
void saveToFile();
void goToStart();
void nextTick();
int getCurrentTick();
int getLengthLeft(int track);
int getPreviousNote(int track);
void addNote(int track, int note, int length);

bool be_isRep(int track, int note);

#define C5 84
#define B4 83
#define AS4 82
#define A4 81
#define GS4 80
#define G4 79
#define FS4 78
#define F4 77
#define E4 76
#define DS4 75
#define D4 74
#define CS4 73
#define C4 72
#define B3 71
#define AS3 70
#define A3 69
#define GS3 68
#define G3 67
#define FS3 66
#define F3 65
#define E3 64
#define DS3 63
#define D3 62
#define CS3 61
#define C3 60
#define B2 59
#define AS2 58
#define A2 57
#define GS2 56
#define G2 55
#define FS2 54
#define F2 53
#define E2 52
#define DS2 51
#define D2 50
#define CS2 49
#define C2 48
#define B1 47
#define AS1 46
#define A1 45
#define GS1 44
#define G1 43
#define FS1 42
#define F1 41
#define E1 40
#define DS1 39
#define D1 38
#define CS1 37
#define C1 36

int scale[] = { C1, D1, E1, F1, G1, A1, B1,
                C2, D2, E2, F2, G2, A2, B2,
                C3, D3, E3, F3, G3, A3, B3,
                C4, D4, E4, F4, G4, A4, B4,
                C5
                };

#endif
