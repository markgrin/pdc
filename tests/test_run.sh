#!/bin/sh

DIR=`dirname $0`
mkdir $DIR/../images
python $DIR/critical.py
python $DIR/dists.py
python $DIR/busy.py
python $DIR/agents.py
