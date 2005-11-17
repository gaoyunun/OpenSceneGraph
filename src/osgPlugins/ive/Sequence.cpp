/**********************************************************************
 *
 *    FILE:            Sequence.cpp
 *
 *    DESCRIPTION:    Read/Write osg::Sequence in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerate
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 24.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "Sequence.h"
#include "Group.h"

using namespace ive;

void Sequence::write(DataOutputStream* out){
    // Write Sequence's identification.
    out->writeInt(IVESEQUENCE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Group*  group = dynamic_cast<osg::Group*>(this);
    if(group){
        ((ive::Group*)(group))->write(out);
    }
    else
        throw Exception("Sequence::write(): Could not cast this osg::Sequence to an osg::Group.");
    // Write Sequence's properties.

    // Write frame times.
    int size = getNumChildren();
    out->writeInt(size);
    for(int i=0;i<size;i++){
        out->writeFloat(getTime(i));
    }
    // Write loop mode & interval
    osg::Sequence::LoopMode mode;
    int begin, end;
    getInterval(mode, begin, end);
    out->writeInt(mode);
    out->writeInt(begin);
    out->writeInt(end);
    // Write duration
    float speed;
    int nreps;
    getDuration(speed, nreps);
    out->writeFloat(speed);
    out->writeInt(nreps);
    // Write sequence mode
    out->writeInt(getMode());

}

void Sequence::read(DataInputStream* in){
    // Peek on Sequence's identification.
    int id = in->peekInt();
    if(id == IVESEQUENCE){
        // Read Sequence's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Group*  group = dynamic_cast<osg::Group*>(this);
        if(group){
            ((ive::Group*)(group))->read(in);
        }
        else
            throw Exception("Sequence::read(): Could not cast this osg::Sequence to an osg::Group.");
        // Read Sequence's properties
        // Read frame times.
        int size = in->readInt();
        for(int i=0;i<size;i++){
            setTime(i, in->readFloat());
        }
        // Read loop mode & interval
        int mode = in->readInt();
        int begin = in->readInt();
        int end = in->readInt();
        setInterval((osg::Sequence::LoopMode)mode, begin, end);
        // Read duration
        float speed = in->readFloat();
        int nreps = in->readInt();
        setDuration(speed, nreps);
        // Read sequence mode
        setMode((osg::Sequence::SequenceMode)in->readInt());
    }
    else{
        throw Exception("Sequence::read(): Expected Sequence identification.");
    }
}
