# Subtask3 #

Launch the terminal.

# Subsampling #
1. Run the following commands in the terminal .
      - make subsampling
      - ./subsampling (VideoName) (FrameDrop) (VideoName is name of file of which you want to find queue density and FrameDrop is the no of frame you want to skip).
2. You should get output in both terminal and outputsubsampling<FrameDrop>.txt.( you get two columns in which first was time and second is queue density.)

3. your "outputsubsampling(framedrop).txt" file will be save in location "analysis/Subsampling"
4. the runtime will save in time.txt file
5. To get percentage error run the following commands in the terminal.
     - make densityerror.
     - ./densityerror "outputsubsampling(framedrop).txt"(your error will be save in error.txt).

6. To plot the graph run the following commands in the terminal.
     - python3 graph.py "outputsubsampling(framedrop).txt"(your graph will be saved in location "analysis/Subsampling")

7. If you want to compare all outputsubsamling file run the following commands in the terminal of location "analysis/Subsampling".
8. you can run make error and make time command in  the terminal of location "analysis/Subsampling" to plot graph of (time vs parameter) and (error vs parameter)

# Reduce Resolution #
1. Run the following commands in the terminal .

      - make resolution
      - ./subsampling (VideoName) (Factor) (VideoName is name of file of which you want to find queue density and Factor is the no by which you want to            reduce resolution of video)

2. You should get output in both terminal and outputresolution(Factor).txt.( you get two columns in which first was time and second is queue density.)

3. your "outputresolution(Factor).txt" file will be save in location "analysis/Resolution".

4. the runtime will save in time.txt file.

5. To get percentage error run the following commands in the terminal.

      - make densityerror 
      - ./densityerror "outputresolution(Factor).txt"(your error will be save in error.txt)

6. To plot the graph run the following commands in the terminal.
      - python3 graph.py "outputresolution(Factor).txt"(your graph will be saved in location "analysis/Resolution")

7. If you want to compare all outputresolution file run the following commands in the terminal of location "analysis/Subsampling"

8. you can run make error and make time command in the terminal of location "analysis/Resolution" to plot the graph of (time vs parameter) and (error vs parameter).

# Spatial Threading #
1. Run the following commands in the terminal .

      - make spatial
      - ./spatial (VideoName) (PthreadNo) (VideoName is name of file of which you want to find queue density and PthreadNo is the no of thread you want to make)

2. You should get output in both terminal and outputspatial(PthreadNo).txt( you get two columns in which first was time and second is queue density.)

3. your "outputspatial(PthreadNo).txt" file will be save in location "analysis/spatial"

4. the runtime will save in time.txt file

5. To get percentage error run the following commands in the terminal.

      - make densityerror 
      - ./densityerror "outputspatial(PthreadNo).txt."(your error will be save in error.txt)

6. you can run make error and make time command in the terminal of location "analysis/spatial" to plot the graph of (time vs parameter) and (error vs parameter).

7. (PthreadNo).png>represent the cpu usuage at the time of creating "outputspatial(PthreadNo).txt."

# Temporal Threading #
1. Run the following commands in the terminal .

      - make temporal
      - ./temporal (VideoName) (PthreadNo) (VideoName is name of file of which you want to find queue density and PthreadNo is the no of thread you want           to make)

2. You should get output in both terminal and outputtemporal(PthreadNo).txt( you get two columns in which first was time and second is queue density.)

3. your "outputtemporal(PthreadNo).txt" file will be save in location "analysis/Temporal"

4. the runtime will save in time.txt file

5. To get percentage error run the following commands in the terminal.

      - make densityerror 
      - ./densityerror "outputtemporal(PthreadNo).txt."(your error will be save in error.txt)

6. you can run make error and make time command in the terminal of location "analysis/Temporal" to plot the graph of (time vs parameter) and (error vs parameter).

7. (PthreadNo).png represent the cpu usuage at the time of creating "outputtemporal(PthreadNo).txt."
