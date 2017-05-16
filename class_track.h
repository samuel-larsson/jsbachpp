#ifndef CLASS_TRACK
#define CLASS_TRACK

#define MAXNOTES 9999

struct track {
  int melody[MAXNOTES];
  int rhythm[MAXNOTES];
  int intervals[MAXNOTES];
  int leaps[MAXNOTES];

  int index;
};

#endif
