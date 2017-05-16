#include "be_jsbachpp.h"
#include "fe_jsbachpp.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int randNum(){
  return rand() % 4 + 1;
}

bool isZeroLeft(int track){
  return getLengthLeft(track) <= 0 ? true : false;
}

bool isPerfect(int mainNote, int harmonyNote){
  return mainNote - harmonyNote == -7 || mainNote - harmonyNote == 5 ? true : false;
}

bool isInScale(int nextNote){
  for(int i = 0; i < 29; i++){
    if(scale[i] == nextNote){
      return true;
    }
  }
  return false;
}

bool checkNote(int note){
  if(be_isRep(1, note) /*|| be_isDissonant() || be_hasClimax() || be_manyDirChg() || be_isFinalStep() || be_isLeapDirChg() || be_hasConsecLeaps() || be_isSameIntervals() || be_hasNoodling() || be_hasLongRuns() || be_hasTension() || be_hasSeq()*/){

  }
}

void processTick(int track){
  srand(time(0));

  if(isZeroLeft(track)){
    int suggestedNote = rand() % 25 - 12 + getPreviousNote(1);
    while(!checkNote(suggestedNote)){
      cout << getPreviousNote(1) - suggestedNote << endl;
      suggestedNote = rand() % 25 - 12 + getPreviousNote(1);
    }
    addNote(1, suggestedNote, 1);
  }
}

void generateMeasures(int measures){
  initTracks();
  goToStart();

  addNote(1, 60, 1);
  for(int i = 1; i < 4*measures; i++){
    processTick(1);
    nextTick();
  }
  /*for(int i = 0; i < 4*measures; i++){

    nextTick();
  }*/
  saveToFile();
}
