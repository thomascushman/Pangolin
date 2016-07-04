#include "Debug.hpp"

void Debug::Print_Stats(MESSAGE_TYPE type, MidiEvent& currentEvent)
  {
    switch(type)
    {
      case NOTE_ON:
      {
        static int i = 1;
        printf("     %sNOTE ON: %sTIMES CALLED%s: %3d, %sCHANNEL%s: %2d, %sKEY#%s: %3d, %sVELOCITY%s: %3d\n\n", KNRM, KBLU, KNRM, i++, KRED, KNRM, currentEvent.getChannelNibble(), KGRN, KNRM, currentEvent.getKeyNumber(), KYEL, KNRM, currentEvent[2]);
        break;
      }
      case NOTE_OFF:
      {
        static int i = 1;
        printf("    %sNOTE OFF: %sTIMES CALLED%s: %3d, %sCHANNEL%s: %2d\n\n", KNRM, KBLU, KNRM, i++, KRED, KNRM, currentEvent.getChannelNibble());
        break;
      }
      case VOLUME_CHANGE:
      {
        //TODO
        break;
      }
      case TEMPO_CHANGE:
      {
        static int i = 1;
        printf("%sCHANGE TEMPO: %sTIMES CALLED%s: %3d,                                        %sNEW TEMPO%s: %f\n\n", KNRM, KBLU, KNRM, i++, KCYN, KNRM, currentEvent.getTempoBPM());
        break;
      }
    }
  }
