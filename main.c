#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct đại diện một ảnh
typedef struct Image {
    char name[100];
    char date[11]; // format: DD-MM-YYYY
    char description[255];
    int size; // KB
    struct Image* next;
} Image;

Image* head = NULL;

// Hàm xóa màn hình (dùng system("clear") nếu chạy trên Linux)
void clearScreen() {
    system("cls");
}

// Dừng màn hình để người dùng đọc kết quả
void pause() {
    printf("\nPress Enter to continue...");
    getchar(); // Đọc ký tự Enter
    getchar(); // Đọc lần 2 nếu bị skip
}

// Tạo một ảnh mới
Image* createImage() {
    Image* newImage = (Image*)malloc(sizeof(Image));
    if (!newImage) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    printf("Enter photo name: ");
    scanf(" %[^\n]", newImage->name);

    printf("Enter date (DD-MM-YYYY): ");
    scanf(" %[^\n]", newImage->date);

    printf("Enter description: ");
    scanf(" %[^\n]", newImage->description);

    printf("Enter size (KB): ");
    scanf("%d", &newImage->size);

    newImage->next = NULL;
    return newImage;
}

// Thêm ảnh vào cuối danh sách
void addPhoto() {
    Image* newImage = createImage();
    if (!newImage) return;

    if (head == NULL) {
        head = newImage;
    } else {
        Image* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newImage;
    }
    printf("\nPhoto added successfully!\n");
    pause();
}

// Hiển thị tất cả ảnh
void displayPhotos() {
    if (head == NULL) {
        printf("No photos in the album.\n");
        pause();
        return;
    }

    printf("\n%-20s %-12s %-10s %s\n", "Photo Name", "Date", "Size(KB)", "Description");
    printf("------------------------------------------------------------------\n");

    Image* temp = head;
    while (temp != NULL) {
        printf("%-20s %-12s %-10d %s\n", temp->name, temp->date, temp->size, temp->description);
        temp = temp->next;
    }
    pause();
}

// Tìm ảnh theo tên
Image* findPhoto(char* name) {
    Image* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Tìm kiếm ảnh
void searchPhoto() {
    char name[100];
    printf("Enter photo name to search: ");
    scanf(" %[^\n]", name);

    Image* photo = findPhoto(name);
    if (photo) {
        printf("\nPhoto found:\n");
        printf("Name: %s\nDate: %s\nSize: %d KB\nDescription: %s\n",
               photo->name, photo->date, photo->size, photo->description);
    } else {
        printf("Photo not found.\n");
    }
    pause();
}

// Xoá ảnh
void deletePhoto() {
    char name[100];
    printf("Enter photo name to delete: ");
    scanf(" %[^\n]", name);

    Image* temp = head;
    Image* prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Photo not found.\n");
    } else {
        if (prev == NULL) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Photo deleted successfully.\n");
    }
    pause();
}

// Sửa ảnh
void editPhoto() {
    char name[100];
    printf("Enter photo name to edit: ");
    scanf(" %[^\n]", name);

    Image* photo = findPhoto(name);
    if (!photo) {
        printf("Photo not found.\n");
        pause();
        return;
    }

    printf("Editing photo: %s\n", name);
    printf("Enter new date (DD-MM-YYYY): ");
    scanf(" %[^\n]", photo->date);

    printf("Enter new description: ");
    scanf(" %[^\n]", photo->description);

    printf("Enter new size (KB): ");
    scanf("%d", &photo->size);

    printf("Photo updated successfully.\n");
    pause();
}

// Phát hiện ảnh trùng
void detectDuplicates() {
    int found = 0;
    Image* ptr1 = head;

    while (ptr1 != NULL) {
        Image* ptr2 = ptr1->next;
        while (ptr2 != NULL) {
            if (strcmp(ptr1->name, ptr2->name) == 0 &&
                strcmp(ptr1->date, ptr2->date) == 0) {
                printf("Duplicate found: %s on %s\n", ptr1->name, ptr1->date);
                found = 1;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    if (!found)
        printf("No duplicates found.\n");

    pause();
}

// Menu chính
void showMenu() {
    int choice;
    do {
        clearScreen();
        printf("====== Photo Album Manager ======\n");
        printf("1. Add Photo\n");
        printf("2. Delete Photo\n");
        printf("3. Search Photo\n");
        printf("4. Edit Photo\n");
        printf("5. Display All Photos\n");
        printf("6. Detect Duplicates\n");
        printf("0. Exit\n");
        printf("=> Your choice: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice) {
            case 1: addPhoto(); break;
            case 2: deletePhoto(); break;
            case 3: searchPhoto(); break;
            case 4: editPhoto(); break;
            case 5: displayPhotos(); break;
            case 6: detectDuplicates(); break;
            case 0: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n"); pause(); break;
        }
    } while (choice != 0);
}

// Giải phóng bộ nhớ
void freeList() {
    Image* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    showMenu();
    freeList();
    return 0;
}
