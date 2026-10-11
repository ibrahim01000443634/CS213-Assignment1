// FCAI - OOP - 2026 - Assignment 1
// File Name: CS213_A1_T2_S[Section]_[20250005]_[20250580]_[20250734]_[20253046].cpp
// Program Description: Image Processing Program applying various image filters.
//
// Author 1: Ibrahim - 20250005 - [Email] - Filters 1, 5, 9, 13
// Author 2: Mohammed - 20250580 - [Email] - Filters 2, 6, 10, 14
// Author 3: Yassin - 20250734 - [Email] - Filters 3, 7, 11, 15
// Author 4: Khaled - 20253046 - [Email] - Filters 4, 8, 12, 16

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "Image_Class.h"

using namespace std;

void filter1(Image& image)
{
    for (int i = 0; i < image.width; i++)
        for (int j = 0; j < image.height; j++)
        {
            int avg = 0;
            for (int k = 0; k < 3; k++)
                avg += image(i, j, k);
            avg /= 3;
            for (int k = 0; k < 3; k++)
                image(i, j, k) = avg;
        }
}

void filter2(Image& image)
{
    for (int i = 0; i < image.width; i++)
        for (int j = 0; j < image.height; j++)
        {
            int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            int val = (avg >= 127) ? 255 : 0;
            for (int k = 0; k < 3; k++)
                image(i, j, k) = val;
        }
}

void filter3(Image& image)
{
    for (int i = 0; i < image.width; i++)
        for (int j = 0; j < image.height; j++)
            for (int k = 0; k < 3; k++)
                image(i, j, k) = 255 - image(i, j, k);
}

void filter4(Image& image)
{
    int frameSize = min(15, min(image.width / 2, image.height / 2));
    if (frameSize < 1) return;

    for (int i = 0; i < image.width; i++)
        for (int j = 0; j < image.height; j++)
            if (i < frameSize || i >= image.width - frameSize ||
                j < frameSize || j >= image.height - frameSize)
                for (int k = 0; k < 3; k++)
                    image(i, j, k) = 255;
}

void filter5(Image& image)
{
    int choice;
    cout << "\n--- Flip Options ---\n1. Horizontal Flip\n2. Vertical Flip\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        for (int y = 0; y < image.height; y++)
            for (int x = 0; x < image.width / 2; x++)
                for (int c = 0; c < 3; c++)
                {
                    int otherX = image.width - 1 - x;
                    int temp = image(x, y, c);
                    image(x, y, c) = image(otherX, y, c);
                    image(otherX, y, c) = temp;
                }
    }
    else if (choice == 2)
    {
        for (int x = 0; x < image.width; x++)
            for (int y = 0; y < image.height / 2; y++)
                for (int c = 0; c < 3; c++)
                {
                    int otherY = image.height - 1 - y;
                    int temp = image(x, y, c);
                    image(x, y, c) = image(x, otherY, c);
                    image(x, otherY, c) = temp;
                }
    }
    else cout << "Invalid choice. Image unchanged.\n";
}

void filter6(Image& image)
{
    int degree;
    cout << "\n--- Rotate Options ---\nAvailable degrees: 90, 180, 270\nEnter degree: ";
    cin >> degree;

    if (degree == 90 || degree == 270)
    {
        Image rotated(image.height, image.width);
        for (int x = 0; x < image.width; x++)
            for (int y = 0; y < image.height; y++)
                for (int c = 0; c < 3; c++)
                {
                    if (degree == 90)
                        rotated(image.height - 1 - y, x, c) = image(x, y, c);
                    else
                        rotated(y, image.width - 1 - x, c) = image(x, y, c);
                }
        image = rotated;
    }
    else if (degree == 180)
    {
        Image rotated(image.width, image.height);
        for (int x = 0; x < image.width; x++)
            for (int y = 0; y < image.height; y++)
                for (int c = 0; c < 3; c++)
                    rotated(image.width - 1 - x, image.height - 1 - y, c) = image(x, y, c);
        image = rotated;
    }
    else cout << "Invalid degree. Image unchanged.\n";
}

void filter7(Image& image)
{
    int choice, percent;
    cout << "\n--- Darken / Lighten Options ---\n1. Darken\n2. Lighten\nChoose option: ";
    cin >> choice;
    if (choice != 1 && choice != 2)
    {
        cout << "Invalid choice. Image unchanged.\n";
        return;
    }

    cout << "Enter percentage (0-100): ";
    cin >> percent;
    while (percent < 0 || percent > 100)
    {
        cout << "Enter a percentage from 0 to 100: ";
        cin >> percent;
    }

    double factor = percent / 100.0;
    for (int x = 0; x < image.width; x++)
        for (int y = 0; y < image.height; y++)
            for (int c = 0; c < 3; c++)
            {
                int value = image(x, y, c);
                if (choice == 1) value = static_cast<int>(value * (1.0 - factor));
                else value = static_cast<int>(value + (255 - value) * factor);
                image(x, y, c) = min(255, max(0, value));
            }
}

Image filter8(const Image& image, int newWidth, int newHeight)
{
    Image resized(newWidth, newHeight);
    for (int x = 0; x < newWidth; x++)
        for (int y = 0; y < newHeight; y++)
        {
            int oldX = x * image.width / newWidth;
            int oldY = y * image.height / newHeight;
            for (int c = 0; c < 3; c++)
                resized(x, y, c) = image(oldX, oldY, c);
        }
    return resized;
}

Image filter9(const Image& image1, const Image& image2)
{
    int type;
    cout << "\n--- Merge Options ---\n1. Common area (minimum dimensions)\n2. Resize both to maximum dimensions\nChoose merge type: ";
    cin >> type;

    if (type != 1 && type != 2)
    {
        cout << "Invalid choice. Merge cancelled.\n";
        return image1;
    }

    int width, height;
    Image first = image1;
    Image second = image2;

    if (type == 1)
    {
        width = min(image1.width, image2.width);
        height = min(image1.height, image2.height);
    }
    else
    {
        width = max(image1.width, image2.width);
        height = max(image1.height, image2.height);
        first = filter8(image1, width, height);
        second = filter8(image2, width, height);
    }

    Image merged(width, height);
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            for (int c = 0; c < 3; c++)
                merged(x, y, c) = (first(x, y, c) + second(x, y, c)) / 2;
    return merged;
}

void filter10(Image& image)
{
    Image result = image;
    for (int x = 0; x < image.width - 1; x++)
        for (int y = 0; y < image.height - 1; y++)
        {
            int current = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
            int right = (image(x + 1, y, 0) + image(x + 1, y, 1) + image(x + 1, y, 2)) / 3;
            int down = (image(x, y + 1, 0) + image(x, y + 1, 1) + image(x, y + 1, 2)) / 3;
            int edge = abs(current - right) + abs(current - down);
            int val = (edge > 30) ? 0 : 255;
            for (int c = 0; c < 3; c++) result(x, y, c) = val;
        }
    image = result;
}

Image filter11(const Image& image)
{
    int x, y, w, h;
    cout << "\n--- Crop Image ---\n";
    cout << "Image size: " << image.width << " x " << image.height << '\n';
    cout << "Enter starting point x y: ";
    cin >> x >> y;
    cout << "Enter crop width and height: ";
    cin >> w >> h;

    while (x < 0 || y < 0 || w <= 0 || h <= 0 ||
           x + w > image.width || y + h > image.height)
    {
        cout << "Invalid crop area. Please try again.\n";
        cout << "Enter starting point x y: ";
        cin >> x >> y;
        cout << "Enter crop width and height: ";
        cin >> w >> h;
    }

    Image cropped(w, h);
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            for (int c = 0; c < 3; c++)
                cropped(i, j, c) = image(x + i, y + j, c);
    return cropped;
}

void filter12(Image& image)
{
    int level;
    cout << "\n--- Blur Filter ---\nEnter blur level (1 or higher): ";
    cin >> level;
    while (level < 1)
    {
        cout << "Enter a level of 1 or higher: ";
        cin >> level;
    }

    Image result = image;
    for (int x = 0; x < image.width; x++)
        for (int y = 0; y < image.height; y++)
            for (int c = 0; c < 3; c++)
            {
                int sum = 0, count = 0;
                for (int dx = -level; dx <= level; dx++)
                    for (int dy = -level; dy <= level; dy++)
                    {
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height)
                        {
                            sum += image(nx, ny, c);
                            count++;
                        }
                    }
                result(x, y, c) = sum / count;
            }
    image = result;
}

void filter13(Image& image)
{
    for (int x = 0; x < image.width; x++)
        for (int y = 0; y < image.height; y++)
            for (int c = 0; c < 3; c++)
                image(x, y, c) = min(255, static_cast<int>(image(x, y, c) * 1.5));
}

void filter14(Image& image)
{
    for (int x = 0; x < image.width; x++)
        for (int y = 0; y < image.height; y++)
            if (y % 4 == 0)
                for (int c = 0; c < 3; c++)
                    image(x, y, c) = image(x, y, c) / 2;
}

void filter15(Image& image)
{
    for (int x = 0; x < image.width; x++)
        for (int y = 0; y < image.height; y++)
        {
            image(x, y, 1) = image(x, y, 1) / 2;
            image(x, y, 2) = 255;
        }
}

void filter16(Image& image)
{
    for (int x = 0; x < image.width; x++)
        for (int y = 0; y < image.height; y++)
        {
            image(x, y, 0) = 255;
            image(x, y, 1) = 255 - image(x, y, 1);
            image(x, y, 2) = 255 - image(x, y, 2);
        }
}

int main()
{
    string filename;
    cout << "Enter image filename to load (example: luffy.jpg): ";
    cin >> filename;

    Image image(filename);
    bool running = true;

    while (running)
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
        cout << "20. Save Current Image\n";
        cout << "88. Load New Image\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0)
        {
            char saveBeforeExit;
            cout << "Save current image before exit? (y/n): ";
            cin >> saveBeforeExit;
            if (saveBeforeExit == 'y' || saveBeforeExit == 'Y')
            {
                string saveFilename;
                cout << "Enter filename (example: result.png): ";
                cin >> saveFilename;
                image.saveImage(saveFilename);
                cout << "Image saved.\n";
            }
            running = false;
        }
        else if (choice == 1) { filter1(image); cout << "Grayscale applied.\n"; }
        else if (choice == 2) { filter2(image); cout << "Black and white applied.\n"; }
        else if (choice == 3) { filter3(image); cout << "Invert applied.\n"; }
        else if (choice == 4) { filter4(image); cout << "Frame applied.\n"; }
        else if (choice == 5) filter5(image);
        else if (choice == 6) filter6(image);
        else if (choice == 7) filter7(image);
        else if (choice == 8)
        {
            int newWidth, newHeight;
            cout << "Enter new width and height: ";
            cin >> newWidth >> newHeight;
            if (newWidth > 0 && newHeight > 0)
            {
                image = filter8(image, newWidth, newHeight);
                cout << "Resize applied.\n";
            }
            else cout << "Invalid dimensions. Image unchanged.\n";
        }
        else if (choice == 9)
        {
            string secondFilename;
            cout << "Enter second image filename: ";
            cin >> secondFilename;
            Image secondImage(secondFilename);
            image = filter9(image, secondImage);
            cout << "Merge applied (if valid).\n";
        }
        else if (choice == 10) { filter10(image); cout << "Edge detection applied.\n"; }
        else if (choice == 11) { image = filter11(image); cout << "Crop applied.\n"; }
        else if (choice == 12) { filter12(image); cout << "Blur applied.\n"; }
        else if (choice == 13) { filter13(image); cout << "Sunlight applied.\n"; }
        else if (choice == 14) { filter14(image); cout << "TV lines applied.\n"; }
        else if (choice == 15) { filter15(image); cout << "Purple filter applied.\n"; }
        else if (choice == 16) { filter16(image); cout << "Infrared applied.\n"; }
        else if (choice == 20)
        {
            string saveFilename;
            cout << "Enter filename to save (example: result.png): ";
            cin >> saveFilename;
            image.saveImage(saveFilename);
            cout << "Image saved successfully.\n";
        }
        else if (choice == 88)
        {
            cout << "Enter new image filename: ";
            cin >> filename;
            image = Image(filename);
            cout << "New image loaded (make sure the file exists in the project folder).\n";
        }
        else cout << "Invalid choice. Please try again.\n";
    }

    return 0;
}
