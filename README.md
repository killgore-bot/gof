Game of life Project Introduction:

To design and implement John Horton Conway's "Game of Life" program  in  C.Game  of  Life  is  a  simulation  designed  with  certain  rules  with  an unpredictable  outcome where a unit of location can accommodate one cell and each cell would have eight neighboring cells, the birth,death or survival of these cells depends on their neighbors. Every cell maybe in a live state or dead state                                                                                                                   Each cell with one or no neighbor dies, as if by lonelinessEach cell with four or more neighbors dies, as if by overpopulationEach cell with two or three neighbors survivesProgram Design:Begin  by  creating  an  array  with  random  1's  and  0's (1's signifying live state and 0's signifying the dead state)  and  a  copy  of  an  original  array .  As  per  the  rules  two  main  functions  were  to  count  the  neighboring  cells  and  second  function  to  apply  the  rules  to  determine  the  live  state  or  dead  state  of  all  the  cells  in  the  next  generation.

Sequential (C) Test Case:
Time -766.8900  sec

OpenMP Test case
Time - 104.18 sec (20 threads)

OpenMPI Test case
Time - 63.08 sec (no.of process -32)

CUDA (GPU) Test case
Time - 29.59 sec

Speedup - 25.91

(*no of itterations is 5000 for all test cases and grid size is 5000X5000)

(Tested on the DMC cluster| Alabama Super Computer)
