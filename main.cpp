// // // FCAI – OOP – 2026 - Assignment 1
// // // File Name: CS112_A1_T2_S[Section]_[20250005]_[20250580]_[20250734]_[20253046].cpp
// // // Program Description: Image Processing Program applying various image filters.
// // //
// // // Author 1 and ID and Email: [Ibrahim] - [20250005] - [Email] - (Filter 1, 5,9,13)
// // // Author 2 and ID and Email: [Mohammed] - [20250580] - [Email] - (Filter 2, 6,10,14)
// // // Author 3 and ID and Email: [Yassin] - [20250734] - [Email] - (Filter 3,7,11,15)
// // // Author 4 and ID and Email: [Khaled] - [20253046] - [Email] - (Filter 4,8,12,16)






#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

void filter1(Image image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int avg = 0;

            for (int k = 0; k < image.channels; k++)
            {
                avg += image(i, j, k);
            }

            avg = avg / image.channels;

            for (int k = 0; k < image.channels; k++)
            {
                image(i, j, k) = avg;
            }
        }
    }
    image.saveImage("grayscale_luffy.png");
    cout << "Saved as grayscale_luffy.png" << endl;
}

void filter2(Image image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int avg = (image(i, j, 0) +
                       image(i, j, 1) +
                       image(i, j, 2)) / 3;

            int val;

            if (avg >= 127)
                val = 255;
            else
                val = 0;

            for (int k = 0; k < 3; k++)
            {
                image(i, j, k) = val;
            }
        }
    }
    image.saveImage("black_white_luffy.png");
    cout << "Saved as black_white_luffy.png" << endl;
}

void filter3(Image image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            image(i, j, 0) = 255 - image(i, j, 0);
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }
    image.saveImage("invert_luffy.png");
    cout << "Saved as invert_luffy.png" << endl;
}

void filter4(Image image)
{
    int frame_Size = 15;

    for (int i = 0; i < image.width; i++)
    {
        for (int k = 0; k < image.channels; k++)
        {
            for (int j = 0; j < frame_Size; j++)
            {
                image(i, j, k) = 255;
            }

            for (int j = image.height - frame_Size; j < image.height; j++)
            {
                image(i, j, k) = 255;
            }
        }
    }

    for (int j = 0; j < image.height; j++)
    {
        for (int k = 0; k < image.channels; k++)
        {
            for (int i = 0; i < frame_Size; i++)
            {
                image(i, j, k) = 255;
            }

            for (int i = image.width - frame_Size; i < image.width; i++)
            {
                image(i, j, k) = 255;
            }
        }
    }
    image.saveImage("frame_luffy.png");
    cout << "Saved as frame_luffy.png" << endl;
}

void filter5(Image image)
{
    int choice;
    cout << "\n--- Flip Options ---\n";
    cout << "1. Horizontal Flip\n";
    cout << "2. Vertical Flip\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1)
    {
        for (int i = 0; i < image.height; i++)
        {
            for (int k = 0; k < image.width / 2; k++)
            {
                int xx = image.width - (k + 1);

                for (int c = 0; c < image.channels; c++)
                {
                    int temp = image(k, i, c);
                    image(k, i, c) = image(xx, i, c);
                    image(xx, i, c) = temp;
                }
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int k = 0; k < image.height / 2; k++)
            {
                int yy = image.height - (k + 1);

                for (int c = 0; c < image.channels; c++)
                {
                    int temp = image(i, k, c);
                    image(i, k, c) = image(i, yy, c);
                    image(i, yy, c) = temp;
                }
            }
        }
    }
    else
    {
        cout << "Invalid choice!" << endl;
        return;
    }
    image.saveImage("flip_luffy.png");
    cout << "Saved as flip_luffy.png" << endl;
}

void filter6(Image image)
{
    int degree;
    cout << "\n--- Rotate Options ---\n";
    cout << "Available degrees: 90, 180, 270\n";
    cout << "Enter degree: ";
    cin >> degree;

    if (degree == 90)
    {
        Image rotatedImage(image.height, image.width);
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < image.channels; k++)
                {
                    rotatedImage(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }
        image = rotatedImage;
    }
    else if (degree == 180)
    {
        Image rotatedImage(image.width, image.height);
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < image.channels; k++)
                {
                    rotatedImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
        image = rotatedImage;
    }
    else if (degree == 270)
    {
        Image rotatedImage(image.height, image.width);
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < image.channels; k++)
                {
                    rotatedImage(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        image = rotatedImage;
    }
    else
    {
        cout << "Invalid degree! Please choose 90, 180, or 270." << endl;
        return;
    }
    image.saveImage("rotate_luffy.png");
    cout << "Saved as rotate_luffy.png" << endl;
}

void filter7(Image image)
{
    int choice;
    cout << "\n--- Darken / Lighten Options ---\n";
    cout << "1) Darken\n";
    cout << "2) Lighten\n";
    cout << "Choose option (1 or 2): ";
    cin >> choice;

    int percent;
    cout << "Enter percentage (0 - 100): ";
    cin >> percent;
    while (percent < 0 || percent > 100) {
        cout << "Invalid! Enter a number from 0 to 100: ";
        cin >> percent;
    }

    double factor = percent / 100.0;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                int value = image(i, j, k);
                if (choice == 1) {
                    value = value - value * factor;
                } else {
                    value = value + (255 - value) * factor;
                }
                image(i, j, k) = value;
            }
        }
    }
    image.saveImage("darken_lighten_luffy.png");
    cout << "Saved as darken_lighten_luffy.png" << endl;
}

Image filter8(Image image, int new_width, int new_height)
{
    Image new_image(new_width, new_height);

    for (int i = 0; i < new_width; i++)
    {
        for (int j = 0; j < new_height; j++)
        {
            int oldI = i * image.width / new_width;
            int oldJ = j * image.height / new_height;

            for (int k = 0; k < image.channels; k++)
            {
                new_image(i, j, k) = image(oldI, oldJ, k);
            }
        }
    }

    return new_image;
}

Image filter9(Image image1, Image image2)
{
    int type;
    cout << "\n--- Merge Options ---\n";
    cout << "1) Common area (min dimensions)\n";
    cout << "2) Max area (resize to max dimensions)\n";
    cout << "Choose merge type (1 or 2): ";
    cin >> type;

    if (type == 1)
    {
        int minheight = min(image1.height, image2.height);
        int minwidth = min(image1.width, image2.width);

        Image image3(minwidth, minheight);

        for (int i = 0; i < minwidth; i++)
        {
            for (int j = 0; j < minheight; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int newimage =
                        (image1(i, j, k) + image2(i, j, k)) / 2;

                    image3(i, j, k) = newimage;
                }
            }
        }

        return image3;
    }

    else
    {
        int maxheight = max(image1.height, image2.height);
        int maxwidth = max(image1.width, image2.width);

        Image resized1 = filter8(image1, maxwidth, maxheight);
        Image resized2 = filter8(image2, maxwidth, maxheight);

        Image image3(maxwidth, maxheight);

        for (int i = 0; i < maxwidth; i++)
        {
            for (int j = 0; j < maxheight; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int newimage =
                        (resized1(i, j, k) + resized2(i, j, k)) / 2;

                    image3(i, j, k) = newimage;
                }
            }
        }

        return image3;
    }
}

void filter10(Image image)
{
    Image result = image;

    for (int i = 0; i < image.width - 1; i++) {
        for (int j = 0; j < image.height - 1; j++) {
            int current = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            int right = (image(i + 1, j, 0) + image(i + 1, j, 1) + image(i + 1, j, 2)) / 3;
            int down = (image(i, j + 1, 0) + image(i, j + 1, 1) + image(i, j + 1, 2)) / 3;
            int edge = abs(current - right) + abs(current - down);

            unsigned char val;
            if (edge > 30) {
                val = 0;
            } else {
                val = 255;
            }
            result(i, j, 0) = val;
            result(i, j, 1) = val;
            result(i, j, 2) = val;
        }
    }
    result.saveImage("edge_luffy.png");
    cout << "Saved as edge_luffy.png" << endl;
}

void filter11(Image image)
{
    int x, y, w, h;
    cout << "\n--- Crop Image ---" << endl;
    cout << "Image size is " << image.width << " x " << image.height << endl;

    cout << "Enter starting point (x y): ";
    cin >> x >> y;
    cout << "Enter width and height (W H): ";
    cin >> w >> h;

    while (x < 0 || y < 0 || w <= 0 || h <= 0 ||
           x + w > image.width || y + h > image.height) {
        cout << "Invalid! The area must be inside the image." << endl;
        cout << "Enter starting point (x y): ";
        cin >> x >> y;
        cout << "Enter width and height (W H): ";
        cin >> w >> h;
    }

    Image cropped(w, h);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < image.channels; k++) {
                cropped(i, j, k) = image(x + i, y + j, k);
            }
        }
    }
    cropped.saveImage("crop_luffy.png");
    cout << "Saved as crop_luffy.png" << endl;
}

void filter12(Image image) {
    int level;
    cout << "\n--- Blur Filter ---" << endl;
    cout << "Enter blur level (1 for light blur, 2 or more for stronger blur): ";
    cin >> level;
    Image result = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                int sum = 0;
                int count = 0;
                for (int x = -level; x <= level; x++) {
                    for (int y = -level; y <= level; y++) {
                        int nx = i + x;
                        int ny = j + y;
                        if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
                            sum += image(nx, ny, k);
                            count++;
                        }
                    }
                }
                result(i, j, k) = sum / count;
            }
        }
    }
    result.saveImage("blur_luffy.png");
    cout << "Saved as blur_luffy.png" << endl;
}

void filter13(Image image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < image.channels; k++)
            {
                int newpic = image(i, j, k) * 1.5;

                if (newpic > 255)
                    newpic = 255;

                image(i, j, k) = newpic;
            }
        }
    }
    image.saveImage("sunlight_luffy.png");
    cout << "Saved as sunlight_luffy.png" << endl;
}

void filter14(Image image)
{
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            if (j % 4 == 0) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = image(i, j, k) / 2;
                }
            }
        }
    }
    image.saveImage("tv_luffy.png");
    cout << "Saved as tv_luffy.png" << endl;
}

void filter15(Image image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            image(i, j, 1) = image(i, j, 1) / 2;
            image(i, j, 2) = 255;
        }
    }
    image.saveImage("purple_luffy.png");
    cout << "Saved as purple_luffy.png" << endl;
}

void filter16(Image image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            image(i, j, 0) = 255;
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }
    image.saveImage("infrared_luffy.png");
    cout << "Saved as infrared_luffy.png" << endl;
}

int main()
{
    Image image("luffy.jpg");

    while (true)
    {
        cout << "\n==============================\n";
        cout << "       IMAGE PROCESSING       \n";
        cout << "==============================\n";
        cout << "1. Grayscale\n";
        cout << "2. Black and White\n";
        cout << "3. Invert Image\n";
        cout << "4. Frame Image\n";
        cout << "5. Flip Image\n";
        cout << "6. Rotate Image\n";
        cout << "7. Darken / Lighten Image\n";
        cout << "8. Resize Image\n";
        cout << "9. Merge Images\n";
        cout << "10. Detect Edges Filter\n";
        cout << "11. Crop Image\n";
        cout << "12. Blur Image\n";
        cout << "13. Sunlight Filter\n";
        cout << "14. TV Lines Filter\n";
        cout << "15. Purple Filter\n";
        cout << "16. Infrared Filter\n";
        cout << "20. Save Image\n";
        cout << "88. Load New Image\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        if (choice == 1)
            filter1(image);

        else if (choice == 2)
            filter2(image);

        else if (choice == 3)
            filter3(image);

        else if (choice == 4)
            filter4(image);

        else if (choice == 5)
            filter5(image);

        else if (choice == 6)
            filter6(image);

        else if (choice == 7)
            filter7(image);

        else if (choice == 8)
        {
            int new_width, new_height;
            cout << "\n--- Resize Image ---" << endl;
            cout << "Enter new width and height: ";
            cin >> new_width >> new_height;
            Image resized = filter8(image, new_width, new_height);
            resized.saveImage("resize_luffy.png");
            cout << "Saved as resize_luffy.png" << endl;
        }

        else if (choice == 9)
        {
            string filename2;
            cout << "\n--- Merge Images ---" << endl;
            cout << "Enter second image name to merge (e.g., mario.bmp): ";
            cin >> filename2;
            Image image2(filename2);
            Image merged = filter9(image, image2);
            merged.saveImage("merge_luffy.png");
            cout << "Saved as merge_luffy.png" << endl;
        }

        else if (choice == 10)
            filter10(image);

        else if (choice == 11)
            filter11(image);

        else if (choice == 12)
            filter12(image);

        else if (choice == 13)
            filter13(image);

        else if (choice == 14)
            filter14(image);

        else if (choice == 15)
            filter15(image);

        else if (choice == 16)
            filter16(image);

        else if (choice == 88)
        {
            string filename;
            cout << "Enter new image name: ";
            cin >> filename;
            image = Image(filename);
            cout << "Loaded new image successfully!" << endl;
        }

        else if (choice == 20)
        {
            string saveFilename;
            cout << "Enter filename to save: ";
            cin >> saveFilename;
            image.saveImage(saveFilename);
            cout << "Image saved successfully!" << endl;
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}