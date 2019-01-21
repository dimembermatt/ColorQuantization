# ColorQuantization
###### Jan 2019
Matthew Yu
C++ Program for quantizing colors in images using an implementation of the median cut algorithm.

![Sunflower.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/sunflower1.jpg)
![Quantized Sunflower with 20 bins.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/test_results/S1_20bins.png)
![Quantized Sunflower with 47 bins.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/test_results/S1_47bins.png)
![Quantized Sunflower with 93 bins.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/test_results/S1_93bins.png)

### INSTRUCTIONS (ubuntu/linux):
1. With the binary imgQuant and a /data folder with images in it
2. run ./imgQuant
3. type a file in /data to access (i.e. 'launch.png')   
4. enter a max bucket size (larger images tend to output a smaller percentage of bins than max)
5. enter image scaling (>= 1, rec is 1|2)
5. Quantized picture outputs!

### OPTIONAL COMMANDS
After generating the picture, OfApp accepts the following commands by keyboard:
- _'s'_: saves the image under 'Color_Quant[i].jpg' (colors are inverted though for some reason)
- _'r'_: reruns the program (enter in different input)
- _'c'_: returns the credits and exits the program (Program can also be exited by ctrl+c in the console or esc in the window).


If you're interested at looking at the OF code to uses the colorQuantizer to make this program, please contact dimembermatt@gmail.com.

### BUGS (OR FEATURES) to be fixed:
1. Program crashes trying to load an invalid image. (currently no error checking for OF img.load(), although it can be fixed through checking the file path)
    - Solution: rerun the program again with valid image name.
2. Program crashes when image scaling inputted is 0 or NaN. (typechecking and bounds checking upcoming).
    - Solution: input a number >= 1
