# ColorQuantization
###### Jan 2019
Matthew Yu
C++ Program for quantizing colors in images using an implementation of the median cut algorithm.

![Sunflower.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/sunflower1.jpg)
![Quantized Sunflower with 35 bins.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/test_results/S1_35Bin.png)
![Quantized Sunflower with 79 bins.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/test_results/S4_79Bin.png)
![Quantized Sunflower with 155 bins.](https://github.com/dimembermatt/ColorQuantization/blob/master/data/test_results/S5_155Bin.png)

### INSTRUCTIONS (ubuntu/linux):
1. With the binary imgQuant and a /data folder with images in it
2. run ./imgQuant
3. type a file in /data to access (i.e. 'launch.png')   
4. enter a min bucket size (this is roughly 2/3rd of the number of the buckets generated)
5. Quantized picture outputs!

### OPTIONAL COMMANDS
After generating the picture, OfApp accepts the following commands by keyboard:
- _'s'_: saves the image under 'Color_Quant[i].jpg' (colors are inverted though for some reason)
- _'r'_: reruns the program (enter in different input)
- _'c'_: returns the credits and exits the program (Program can also be exited by ctrl+c in the console or esc in the window).


If you're interested at looking at the OF code to uses the colorQuantizer to make this program, please contact dimembermatt@gmail.com.

