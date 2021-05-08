# routing4imagery

routing4imagery is a set of programs that is able to convert an OSM PBF file into a text file with an optimized path that solves the
Chinese postman problem. The Chinese postman problem attempts to find the shortest path that visits every edge in an undirected graph.
To solve this, we created a workflow using several open source and custom programs to accomplish this task efficiently. This pipeline can
be automated using bash scripting, given that all packages required are correctly installed.

# Requirements

All processes are best optimized to be done within the unix terminal. A list of packages and applications with versions later or same as listed below should be installed
for best results:
* g++ 7.5.0
* python 3.8
  * networkx 2.0
* cargo 1.47

# Usage

The file, runrouting4imagery.sh, should prompt the user the files they would like to input to generate a route. There will be an output csv file
that represents the order of nodes in the route.
* The input of the files should be directly exported from the HOT Export tool linked [here](https://export.hotosm.org/en/v3/). The feature selection
settings will also be included in this github named hotexportconfig.txt.

# Workflow

We will take the exported PBF file from HOT export tool and create two csv files as output. One will contain a list of nodes and the other will contain a list of edges
and their lengths. From there, the two files undergo preprocessing and reformatting to be compatible with the python package that will compute the Chinese 
postman route.

There is a separate python script which is not part of the main workflow, but is useful to visualize the graph and overall route as an image.

Open source github packgages that are used within this pipeline will be automatically cloned into the working directory through the bash script.

# Notes

The efficiency of the Chinese postman problem is considerably slow. As a result, running very large inputs may take a very long time. In addition,
this is not a finished product, as we still continue to improve the workflow and fix bugs that arise.
