//rgb to yuv conversion yuv422 format
#include<stdio.h>
#include<stdlib.h>

int i,j;

int yuv_rgb(int *y ,int *u, int *v, int *R, int *G, int *B);

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} rgb;


void crop_rgb_image(const char* input_filename, int width, int height, int crop_x, int crop_y, int crop_width, int crop_height) {

   if(height < crop_height) { 
   printf("height value is high\r\n");
   return;
   }
   if(width  < crop_width){
   printf("width value is high\r\n");  
   return;
   }
    FILE* input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return;
    }

    // Calculate cropping boundaries
    int crop_x_end = crop_x + crop_width;
    int crop_y_end = crop_y + crop_height;
    int  y_, u, v, R, G, B;    
    

    // Allocate memory for input and output pixel arrays
    rgb* input_pixels = (rgb*)malloc(width * height * sizeof( rgb));
    
    if (input_pixels == NULL) {
    printf("Error allocating memory for input pixels\n");
    fclose(input_file);
    return;
    }
    
    // Read input pixel data
   size_t num_pixels_read = fread(input_pixels, sizeof(rgb), width * height, input_file);
   
   if (num_pixels_read != width * height) {
    printf("Error reading input file\n");
    fclose(input_file);
    return;
   }
    fclose(input_file);

    printf("ENTER THE YUV VALUE\r\n");
    scanf("%d%d%d",&y_, &u, &v);
    
    //convert rgb value into yuv value and stored in structure
    yuv_rgb(&y_ , &u, &v, &R, &G, &B);
    rgb value = {R , G, B};
    
    // Crop image
    int output_index = 0;
    int x, y;
    for (y = crop_y; y < crop_y_end; y++) {
        for (x = crop_x; x < crop_x_end; x++) {
            int input_index = y * width + x;
            input_pixels[input_index] = value;
            output_index++;
        }
    }

    // Write cropped image to output file
    FILE* output_file = fopen(input_filename, "wb");
    if (output_file != NULL) {
        fwrite(input_pixels, sizeof(rgb), width * height, output_file);
        fclose(output_file);
    } else {
        printf("Error opening output file\n");
    }

    // Free memory
    free(input_pixels);
}

void RGBtoYUV(const char* input_filename, const char* output_filename, int width, int height) {
    int i, j;
    int r, g, b;
    int y1, u, y2, v;

    FILE* input_file = fopen(input_filename, "rb");

    if (input_file == NULL) {
        printf("Error opening input file\n");
        return;
    }

    rgb* rgbImage = (rgb*)malloc(width * height * sizeof(rgb));
    unsigned char* yuvImage = (unsigned char*)malloc(width * height * 2 * sizeof(unsigned char));

    fread(rgbImage, sizeof(rgb), width * height, input_file);

    fclose(input_file);

    unsigned char* yuvPtr = yuvImage;
    unsigned char* rgbPtr = (unsigned char*)rgbImage;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j += 2) {
            // Get RGB values for the first pixel
            r = *rgbPtr++;
            g = *rgbPtr++;
            b = *rgbPtr++;

            // Convert RGB to YUV for the first pixel
            y1 = (int)(0.299 * r + 0.587 * g + 0.114 * b);
            u = (int)(-0.169 * r - 0.331 * g + 0.5 * b) + 128;
            v = (int)(0.5 * r - 0.419 * g - 0.081 * b) + 128;

            // Get RGB values for the second pixel
            r = *rgbPtr++;
            g = *rgbPtr++;
            b = *rgbPtr++;

            // Convert RGB to YUV for the second pixel
            y2 = (int)(0.299 * r + 0.587 * g + 0.114 * b);

            // Store YUV values in the output image
            *yuvPtr++ = (unsigned char)y1;
            *yuvPtr++ = (unsigned char)u;
            *yuvPtr++ = (unsigned char)y2;
            *yuvPtr++ = (unsigned char)v;
        }
    }

    FILE* output_file = fopen(output_filename, "wb");
    if (output_file != NULL) {
        fwrite(yuvImage, sizeof(unsigned char), width * height * 2, output_file);
        fclose(output_file);
    } else {
        printf("Error opening output file\n");
    }

    free(rgbImage);
    free(yuvImage);
}

void rgb_conversion(int r, int g, int b, int height, int width) 
{
	rgb *pixel = (rgb*) malloc((height * width) * sizeof(pixel));
        rgb value = {r , g, b};
        for(j=0; j < height; j++) {
        	for(i=0; i < width; i++) {
        		pixel[ j * width + i] = value;
        		printf(" %d %d %d ", pixel[j * width + i].red, pixel[j * width + i].green, pixel[j * width + i].blue);
        		printf("\n");
        	}
        }      	 
        FILE *file = fopen("nirmal.rgb", "wb"); 
        if (file != NULL) {
      		//  fprintf(file, "P6\n%d %d\n255\n", width, height);
       	fwrite(pixel,sizeof(rgb), height * width, file);
       	fclose(file);
       }
       free(pixel); 
}

void RGBtoYUV_422_yuyv(const char* input_filename, const char* output_filename, int width, int height) {
    int i, j;
    int r, g, b;
    int y1, u, y2, v;

    FILE* input_file = fopen(input_filename, "rb");

    if (input_file == NULL) {
        printf("Error opening input file\n");
        return;
    }

    rgb* rgbImage = (rgb*)malloc(width * height * sizeof(rgb));
    unsigned char* yuvImage = (unsigned char*)malloc(width * height * 2 * sizeof(unsigned char));

    fread(rgbImage, sizeof(rgb), width * height, input_file);

    fclose(input_file);

    unsigned char* yuvPtr = yuvImage;
    unsigned char* rgbPtr = (unsigned char*)rgbImage;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j += 2) {
            // Get RGB values for the first pixel
            r = *rgbPtr++;
            g = *rgbPtr++;
            b = *rgbPtr++;

            // Convert RGB to YUV for the first pixel
            y1 = (int)(0.299 * r + 0.587 * g + 0.114 * b);
            u = (int)(-0.169 * r - 0.331 * g + 0.5 * b) + 128;
            v = (int)(0.5 * r - 0.419 * g - 0.081 * b) + 128;

            // Get RGB values for the second pixel
            r = *rgbPtr++;
            g = *rgbPtr++;
            b = *rgbPtr++;

            // Convert RGB to YUV for the second pixel
            y2 = (int)(0.299 * r + 0.587 * g + 0.114 * b);

            // Store YUV values in the output image
            *yuvPtr++ = (unsigned char)y1;
            *yuvPtr++ = (unsigned char)u;
            *yuvPtr++ = (unsigned char)y2;
            *yuvPtr++ = (unsigned char)v;
        }
    }

    FILE* output_file = fopen(output_filename, "wb");
    if (output_file != NULL) {
        fwrite(yuvImage, sizeof(unsigned char), width * height * 2, output_file);
        fclose(output_file);
    } else {
        printf("Error opening output file\n");
    }

    free(rgbImage);
    free(yuvImage);
}

void RGBtoI420(const char* input_filename, const char* output_filename, int width, int height) {
    int i, j;
    int r, g, b;
    int y, u, v;

    FILE* input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return;
    }

    rgb* rgbImage = (rgb*) malloc(width * height * sizeof(rgb));
    unsigned char* i420Image = (unsigned char*) malloc(width * height * 3 / 2 * sizeof(unsigned char));

    fread(rgbImage, sizeof(rgb), width * height, input_file);
    fclose(input_file);

    unsigned char* yPtr = i420Image;
    unsigned char* uPtr = i420Image + (width * height);
    unsigned char* vPtr = i420Image + (width * height) + (width * height / 4);

    unsigned char* rgbPtr = (unsigned char*)rgbImage;

    for (i = 0; i < height; i += 1) {
        for (j = 0; j < width; j += 1) {
            // Get RGB values for the first pixel
            r = *rgbPtr++;
            g = *rgbPtr++;
            b = *rgbPtr++;

            // Convert RGB to YUV for the first pixel
            y = (int)(0.299 * r + 0.587 * g + 0.114 * b);
            u = (int)(-0.14713 * r - 0.28886 * g + 0.436 * b) + 128;
            v = (int)(0.615 * r - 0.51498 * g - 0.10001 * b) + 128;

            // Store Y value in the output image
            *yPtr++ = (unsigned char)y;

            // Get RGB values for the second pixel
          //  r = *rgbPtr++;
          //  g = *rgbPtr++;
          //  b = *rgbPtr++;

            // Convert RGB to YUV for the second pixel
          //  y = (int)(0.299 * r + 0.587 * g + 0.114 * b);

            // Store Y value in the output image
           // *yPtr++ = (unsigned char)y;
           
           if(i%2 ==0 && j % 2 == 0) {

            // Store U and V values in the output image
            *uPtr++ = (unsigned char)u;
            *vPtr++ = (unsigned char)v;
            }
        }
    }

    FILE* output_file = fopen(output_filename, "wb");
    if (output_file != NULL) {
        fwrite(i420Image, sizeof(unsigned char), width * height * 3 / 2, output_file);
        fclose(output_file);
    } else {
        printf("Error opening output file\n");
    }

    free(rgbImage);
    free(i420Image);
}



int yuv_rgb(int *y ,int *u, int *v, int *R, int *G, int *B) {

*R = *y + 1.140 *  *v;

*G = *y - 0.395 * *u -0.518 * *v ;

*B = *y + 2.032 * *u;

}

int main()
{
	int height, width, r, g, b, crop_x, crop_y, crop_width, crop_height, ch_k;
	 
	printf("*****ENTER THE HEIGHT AND WIDTH OF THE IMAGE*****\n");
	printf("HEIGHT:");
	scanf("%d",&height);
	printf("WIDTH:");
	scanf("%d",&width);
	printf("*****ENTER THE RGB VALUE*****\n");
	scanf("%d%d%d",&r,&g,&b);
	printf("**if you want to crop that image**\r\n\
	        yes : press 1 \r\n\
	        no  : press 2 \r\n");
	scanf("%d",&ch_k);
	
	//rgb conversion
	rgb_conversion(r, g, b, height, width);
	
       if(ch_k == 1) {
                printf("ENTER THE X-AXIS Y-AXIS CROP_WIDTH  CROP_HEIGHT\r\n");
      		scanf("%d%d%d%d", &crop_x, &crop_y, &crop_width, &crop_height);      	
      		printf("%d,%d,%d,%d,%d,%d\r\n",crop_x,crop_y,crop_width,crop_height,width,height);
                
                //cropping image to change color values	
      		crop_rgb_image("nirmal.rgb", width, height, crop_x, crop_y, crop_width, crop_height);  
      }  
      
      //rgb to yuv conversion
      RGBtoYUV_422_yuyv("nirmal.rgb","yuv422_p.yuv", width, height); 
      
      //rgb to yuv4220 conversion i420 planner
      RGBtoI420("nirmal.rgb", "yuv420_p.yuv", width, height);
}

