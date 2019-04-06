# CMPUT 275 FINAL PROJECT: FFT Visualizer
## Cyrus Diego and Daniel Rojas-Cardona 
--------------------------------------------------------------------------------
# DESCRIPTION:
    Using music files (.wav) as our source of data, we implemented our own
    fast fourier transform (FFT) function that reads in raw audio data and
    performs a fourier transform to determine the frequencies playing at each second.

    The results are then visualized on the screen using a simple bar graph that
    will increase in height depending on the magnitude of the frequencies playing

--------------------------------------------------------------------------------
# LIBRARIES USED:
    - SFML : sudo apt-get install libsfml-dev

--------------------------------------------------------------------------------
# HOW DOES IT WORK?
    1) select a song to analyze

    2) perform FFT on whole song:
        - runs FFT on song (running in O(NlogN) time)
        - stores FFT results in complex "table" / buffer and stores in memory

    3) barSpectrum class reads in one column at a time from complex "table" /
    buffer and calculates the magnitude each bar must increase to
        - each bar represents a frequency from 0 to 5000Hz

    4) slowly increment each bar to target magnitude at 60 fps

    5) once all bars have reached their target magnitude, refresh the buffer
    and get the next column from the table

    6) repeat this process until the entire table has been iterated

--------------------------------------------------------------------------------
# ACKNOWLEDGMENTS:
    - FFT Algorithm
http://people.scs.carleton.ca/~maheshwa/courses/5703COMP/16Fall/FFT_Report.pdf
    - SFML
https://www.sfml-dev.org/index.php
     - Normalization of numbers
https://stats.stackexchange.com/questions/281162/scale-a-number-between-a-range
    - Threads
https://stackoverflow.com/questions/17472827/create-thread-inside-class-with-function-from-same-class
    - Hanning Window
https://stackoverflow.com/questions/3555318/implement-hann-window
    - Stable Partition
https://stackoverflow.com/questions/33787939/sort-vector-by-even-and-odd-indices-c
