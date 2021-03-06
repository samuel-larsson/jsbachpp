#include <iostream>
#include "./include/MidiFile.h"
#include "./include/MidiEvent.h"

using namespace std;

#define MAXNOTES 9999

typedef unsigned char uchar;

struct midisong {
  MidiFile outputfile;
  vector<uchar> midievent;

  int track1Melody[MAXNOTES], track1Rhythm[MAXNOTES];
  int track2Melody[MAXNOTES], track2Rhythm[MAXNOTES];
  int track3Melody[MAXNOTES], track3Rhythm[MAXNOTES];
  int track4Melody[MAXNOTES], track4Rhythm[MAXNOTES];

  int leaps;

  int currIndex1, currIndex2, currIndex3, currIndex4;
  int currLength1, currLength2, currLength3, currLength4;
  int noteLength1, noteLength2, noteLength3, noteLength4;
  int currTick;
  int tpq;    //ticks per quarter
} song ;

void initTracks(){
  for(int i = 0; i < 9999; i++){
    song.track1Melody[i] = -1;
    song.track2Melody[i] = -1;
    song.track3Melody[i] = -1;
    song.track4Melody[i] = -1;
  }

  song.currIndex1 = 0;
  song.currIndex2 = 0;
  song.currIndex3 = 0;
  song.currIndex4 = 0;

  song.outputfile.absoluteTicks();
  song.outputfile.addTrack(4);
  song.midievent.resize(3);        // set the size of the array to 3 bytes
  song.tpq = 120;              // default value in MIDI file is 48
  song.outputfile.setTicksPerQuarterNote(song.tpq);
}

void saveToFile(){
  int i=0;
  int actiontime = 0;      // temporary storage for MIDI event time
  song.midievent[2] = 64;       // store attack/release velocity for note command
  while (song.track1Melody[i] >= 0) {
     song.midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
     song.midievent[1] = song.track1Melody[i];
     song.outputfile.addEvent(1, actiontime, song.midievent);
     actiontime += song.tpq * song.track1Rhythm[i];
     song.midievent[0] = 0x80;     // store a note on command (MIDI channel 1)
     song.outputfile.addEvent(1, actiontime, song.midievent);
     i++;
  }

  i = 0;
  actiontime = 0;
  while (song.track2Melody[i] >= 0) {
     song.midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
     song.midievent[1] = song.track2Melody[i];
     song.outputfile.addEvent(2, actiontime, song.midievent);
     actiontime += song.tpq * song.track2Rhythm[i];
     song.midievent[0] = 0x80;     // store a note on command (MIDI channel 1)
     song.outputfile.addEvent(2, actiontime, song.midievent);
     i++;
  }

  i = 0;
  actiontime = 0;
  while (song.track3Melody[i] >= 0) {
     song.midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
     song.midievent[1] = song.track3Melody[i];
     song.outputfile.addEvent(3, actiontime, song.midievent);
     actiontime += song.tpq * song.track3Rhythm[i];
     song.midievent[0] = 0x80;     // store a note on command (MIDI channel 1)
     song.outputfile.addEvent(3, actiontime, song.midievent);
     i++;
  }

  i = 0;
  actiontime = 0;
  while (song.track4Melody[i] >= 0) {
     song.midievent[0] = 0x90;     // store a note on command (MIDI channel 1)
     song.midievent[1] = song.track4Melody[i];
     song.outputfile.addEvent(4, actiontime, song.midievent);
     actiontime += song.tpq * song.track4Rhythm[i];
     song.midievent[0] = 0x80;     // store a note on command (MIDI channel 1)
     song.outputfile.addEvent(4, actiontime, song.midievent);
     i++;
  }

  song.outputfile.sortTracks();         // make sure data is in correct order
  song.outputfile.write("test.mid"); // write Standard MIDI File twinkle.mid
}

/*** DATA STRUCTURE NAVIGATION ***/
void goToStart(){ song.currTick = 0; }

void nextTick(){
  song.currTick++;
  song.currLength1++;
  song.currLength2++;
  song.currLength3++;
  song.currLength4++;
}

int getCurrentTick(){ return song.currTick; }

int getCurrentLength(int track){
  switch(track){
    case 1:
      return song.currLength1;
    case 2:
      return song.currLength2;
    case 3:
      return song.currLength3;
    case 4:
      return song.currLength4;
    default:
      return 0;
      break;
  }
}

int getLengthLeft(int track){
  switch(track){
    case 1:
      return song.noteLength1 - getCurrentLength(1);
    case 2:
      return song.noteLength2 - getCurrentLength(2);
    case 3:
      return song.noteLength3 - getCurrentLength(3);
    case 4:
      return song.noteLength4 - getCurrentLength(4);
    default:
      return 0;
      break;
  }
}

int getPreviousNote(int track){
  if(song.currTick != 0){
    switch(track){
      case 1:
        return song.track1Melody[song.currIndex1-1];
      case 2:
        return song.track2Melody[song.currIndex2-1];
      case 3:
        return song.track3Melody[song.currIndex3-1];
      case 4:
        return song.track4Melody[song.currIndex4-1];
      default:
        return 0;
        break;
    }
  } else {
    return -1;
  }
}

void addNote(int track, int note, int length){
  switch(track){
    case 1:
      song.track1Melody[song.currIndex1] = note;
      song.track1Rhythm[song.currIndex1] = length;
      song.currLength1 = 0;
      song.noteLength1 = length;
      song.currIndex1++;
      break;
    case 2:
      song.track2Melody[song.currIndex2] = note;
      song.track2Rhythm[song.currIndex2] = length;
      song.currLength2 = 0;
      song.noteLength2 = length;
      song.currIndex2++;
      break;
    case 3:
      song.track3Melody[song.currIndex3] = note;
      song.track3Rhythm[song.currIndex3] = length;
      song.currLength3 = 0;
      song.noteLength3 = length;
      song.currIndex3++;
      break;
    case 4:
      song.track4Melody[song.currIndex4] = note;
      song.track4Rhythm[song.currIndex4] = length;
      song.currLength4 = 0;
      song.noteLength4 = length;
      song.currIndex4++;
      break;
    default:
      break;
  }
}
