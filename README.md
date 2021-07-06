# routing4imagery

routing4imagery is a set of programs that is able to convert an OSM PBF file into a text file with an optimized path that solves the
route inspection problem. The route inspection problem attempts to find the shortest path that visits every edge in an undirected graph.
routing4imagery uses several open-source and custom programs to accomplish this task efficiently. This pipeline can
be automated using bash scripting, given that all packages required are correctly installed.

# Requirements

All processes are best optimized to be done within the unix terminal. A list of packages and applications with versions later or same as listed below should be installed
for best results:
* g++ 7.5.0
* python 3.8
  * networkx 2.0
* cargo 1.47

# Usage

Running runrouting4imagery.sh will prompt the user for the files from which they would like to generate a route. There will be an output csv file
that represents the order of nodes in the route.
* The input of the files should be directly exported from the HOT Export tool linked [here](https://export.hotosm.org/en/v3/). The feature selection
settings will also be included in this repository, named hotexportconfig.txt.

# Workflow

We take the exported PBF file from the HOT export tool and create two csv files. One will contain a list of nodes and the other will contain a list of edges
and their lengths. From there, the two files undergo preprocessing and reformatting to be compatible with a Python package that will solve the route inspection problem.

There is a Python notebook that is distinct from the main workflow but useful to visualize the graph and route.

Open-source Github repositories that are used in this pipeline will be cloned automatically into the working directory.

# Notes

The efficiency of the route inspection problem is considerably slow. As a result, running very large inputs may take a very long time. In addition,
this is not a finished product, and we still continue to improve the workflow and fix bugs that arise. Please submit an issue if you have any feedback/suggestions.
