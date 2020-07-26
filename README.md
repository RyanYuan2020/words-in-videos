# words-in-videos

Author - *Ryan Yuan*

## Intro

A helper for English learner.  
The product plays excerpts of designated local videos of which the dialogue contains the given word, hence helps user to have a better grasp of the word.  The re-play of the excerpt helps users to connect the plot of movie, series with the unfamiliar word.  The simultaneous stimulation of **vision**, **audition** as well as **the memories for the polt**, makes it easier to remember and grip a word.  

## Preparation

1. Download videos player *[PotPlayer](http://potplayer.daum.net/?lang=zh_CN)* on your computer.  
  *The link may be unavailable for Chinese users*
2. Create 2 **different** folders for your subtitle files and videos files **respectively**, aka the root folders.  
3. Duplicate/move your subtitle files & videos files to the folders you created at step 2.  
   It is noteworthy that, the folders will be lexicographically ordered, and the corresponding subtitle file and video file should be in **"the same relative folders"** to their root folders.  
   For example, in my subtitle folder, it looks like this when lexicographically ordered:  
  
   ```c
   [directory]subtitle
   --[file]a subtitle file0.srt
   --[directory]sub_folder_A
     --subtitle file1.ass
   --[file]The last subtitle file.srt
   ```
  
   Correspondingly, my video file should looks like:  
  
   ```c
   [directory]video
   --[file]movie0.mp4
   --[directory]sub_folder_in_video_folder
     --[file]movie1.mp4
   --[file]The last video file.mp4
   ```

4. Write the install path of *PotPlayer*, path of subtitle folder and path of video folder in the proper place in `Main.cpp`.  

## How to use

Input the unfamiliar word encountered, the program will offer several entries of dialogue that contains the given word.  Input the number at the beginning of each entry, the *PotPlayer* would be invoked to play the designated excerpt.  To start another word, input any number that is larger than the index of the last entry.  

## Features

1. The creative way of matching subtitle and video files exempts users of tedious work of file labelling.  

2. The program is able to parse subtitle files with both extensions `.srt` and `.ass`.  
