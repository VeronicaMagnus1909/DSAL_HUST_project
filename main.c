#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct đại diện một ảnh
typedef struct Image {
    char name[100]; // name là kiểu char mảng 
    char date[11]; // format: DD-MM-YYYY
    char description[255]; //Mô tả bức ảnh
    int size; // KB
    struct Image* next;
} Image;

Image* head = NULL; // Biến head toàn cục để lưu trữ đầu danh sách ảnh

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
    Image* newImage = (Image*)malloc(sizeof(Image)); //cấp phát bộ nhớ cho ảnh mới, sử dụng malloc
    //Kiểm tra xem cấp phát thành công không
    if (newImage == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    //Nếu thành công, yêu cầu người dùng nhập thông tin cho ảnh
    // Thông tin bao gồm: name, date, description, size

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
    // Hiển thị thông báo và tạo một ảnh mới, cái
    Image* newImage = createImage();
    if (!newImage) return;
    // Traverse đến cuối danh sách, thêm ảnh vào cuối danh sách
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

    // Tạo giao diện console-based  
    // In tiêu đề bảng
    printf("\n%-20s %-12s %-10s %s\n", "Photo Name", "Date", "Size(KB)", "Description");
    printf("------------------------------------------------------------------\n");

    Image* temp = head;
    // con trỏ temp chạy từ head đến nốt cuối - traverse
    while (temp != NULL) {
        printf("%-20s %-12s %-10d %s\n", temp->name, temp->date, temp->size, temp->description);
        temp = temp->next;
    }
    pause();
}

// Tìm ảnh theo tên
// Nhập vào tên, return con trỏ đến ảnh nếu tìm thấy, NULL nếu không tìm thấy
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
// yêu cầu người dùng nhập tên ảnh cần tìm
// Nếu tìm thấy, hiển thị thông tin ảnh
void searchPhoto() {
    char name[100];
    printf("Enter photo name to search: "); // Nhập tên ảnh cần tìm
    scanf(" %[^\n]", name);

    Image* photo = findPhoto(name); // Tạo con trỏ photo để lưu ảnh tìm được
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
// Idead: Dùng 2 con trỏ: temp để duyệt danh sách, prev để lưu ảnh trước đó; temp tìm thấy ảnh cần xóa, prev sẽ móc nối với cái đằng sau temp
//
void deletePhoto() {
    char name[100];
    printf("Enter photo name to delete: ");
    scanf(" %[^\n]", name);

    Image* temp = head;
    Image* prev = NULL;

    // Nếu temp là NULL, tức là danh sách rỗng, hoặc temp->name khác name, tức là không tìm thấy ảnh cần xóa
    // vòng lặp while chạy đến khi tìm thấy ảnh cần xóa hoặc đến cuối danh sách
    // 2 con trỏ temp và prev sẽ chạy qua từng ảnh trong danh sách
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    //Sau khi vòng lặp while kết thúc, có các trường hợp:
    // 1. temp là NULL: không tìm thấy ảnh cần xóa
    // 2: temp khác null thì lại con 2 trường hợp:
    // 2.1: prev là NULL (lúc này temp đang trỏ vào head) ảnh cần xóa là ảnh đầu tiên, head sẽ trỏ đến ảnh tiếp theo
    // 2.2: prev khác NULL: ảnh cần xóa không phải là ảnh đầu tiên, prev sẽ móc nối với cái đằng sau temp

    if (temp == NULL) {
        printf("Photo not found.\n");
    } else {
        if (prev == NULL) {
            head = temp->next; // Nếu ảnh cần xóa là ảnh đầu tiên, head sẽ trỏ đến ảnh tiếp theo
        } else {
            prev->next = temp->next; // prev móc nối với cái đằng sau temp
        }
        free(temp); // giải phóng bộ nhớ của ảnh đã xóa
        printf("Photo deleted successfully.\n");
    }
    pause();
}

// Sửa ảnh
// Idead: Tìm ảnh theo tên, nếu tìm thấy thì sửa thông tin cho ảnh đó
void editPhoto() {
    char name[100];
    printf("Enter photo name to edit: ");
    scanf(" %[^\n]", name);

    Image* photo = findPhoto(name); // Tạo con trỏ photo (kiểu image) để lưu ảnh tìm được
    // Nếu không tìm thấy ảnh, thông báo và dừng chương trình
    if (!photo) {
        printf("Photo not found.\n");
        pause();
        return;
    }

    // Nếu tìm thấy ảnh, hiển thị thông tin ảnh và yêu cầu người dùng nhập thông tin mới
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
// Idea: Dùng 2 con trỏ: ptr1 để duyệt danh sách, ptr2 để so sánh với các ảnh còn lại

void detectDuplicates() {
    int found = 0; // biến found ban đầu = 0, nếu tìm thấy ảnh trùng thì sẽ set thành 1
    Image* ptr1 = head;

    while (ptr1 != NULL) {
        Image* ptr2 = ptr1->next;
        while (ptr2 != NULL) {
            // có thể thử xem nếu trùng tất cả thuộc tính thì sẽ coi là trùng
            // ở đây mình set tên và ngày giống nhau thì coi là trùng
            if (strcmp(ptr1->name, ptr2->name) == 0 &&
                strcmp(ptr1->date, ptr2->date) == 0) {
                printf("Duplicate found: %s on %s\n", ptr1->name, ptr1->date);
                found = 1;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    // found = 0 có nghĩa là không tìm thấy ảnh trùng
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

// Ta viết các hàm sort name, date, size

//Trước tiên, cần các hàm phụ trợ
// Hàm 1: đếm số lượng ảnh trong danh sách liên kết
int count_nodes(Image* head)
{
    int count = 0;
    while(head)
    {
        count++;
        head = head->next;
    }
    return count;
}

//Hàm 2: tao array -> dien gia tri cua tung link list vao
int fill_array(Image* head, Image** array) // ** :mang chua con tro
{
    int i = 0;
    while (head) {
        array[i++] = head;
        head = head->next;
    }

}

int compare_by_name(const void* a, const void* b) {
    Image* imgA = *(Image**)a;
    Image* imgB = *(Image**)b;
    return strcmp(imgA->name, imgB->name); //string compare
}

int compare_by_date(const void* a, const void* b) {
    Image* imgA = *(Image**)a;
    Image* imgB = *(Image**)b;

    int dayA, monthA, yearA;
    int dayB, monthB, yearB;

    sscanf(imgA->date, "%2d-%2d-%4d", &dayA, &monthA, &yearA);
    sscanf(imgB->date, "%2d-%2d-%4d", &dayB, &monthB, &yearB);

    if (yearA != yearB)
        return yearA - yearB;
    if (monthA != monthB)
        return monthA - monthB;
    return dayA - dayB;
}

int compare_by_size(const void* a, const void* b) {
    Image* imgA = *(Image**)a;
    Image* imgB = *(Image**)b;
    if(imgA->size >= imgB->size) return 1;
    else return -1;
}

void print_sorted_array(Image** array, int size)
{
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Date: %s\n", array[i]->name, array[i]->date);
    }
}

// Có 3 hàm sort
// Hàm 1: Sắp xếp theo tên
void sort_name(Image* head) {
    int size = count_nodes(head);                        // B1: đếm số ảnh
    Image** array = malloc(size * sizeof(Image*)); // B2: cấp phát mảng con trỏ

    fill_array(head, array);                             // B3: chuyển linked list thành mảng

    qsort(array, size, sizeof(Image*), compare_by_name); // B4: sắp xếp theo tên
    // Hoặc dùng: compare_by_date nếu muốn sắp theo ngày

    print_sorted_array(array, size);                     // B5: hiển thị danh sách ảnh đã sắp
    pause(); // wait for user read
    free(array);                                         // Giải phóng bộ nhớ
}

// Hàm 2: Sắp xếp theo ngày
void sort_date(Image* head) {
    int size = count_nodes(head);                        // B1: đếm số ảnh
    Image** array = malloc(size * sizeof(Image*)); // B2: cấp phát mảng con trỏ

    fill_array(head, array);                             // B3: chuyển linked list thành mảng

    qsort(array, size, sizeof(Image*), compare_by_date); // B4: sắp xếp theo tên
    // Hoặc dùng: compare_by_date nếu muốn sắp theo ngày

    print_sorted_array(array, size);                     // B5: hiển thị danh sách ảnh đã sắp
    pause(); // wait for user read
    free(array);                                         // Giải phóng bộ nhớ
}

// Hàm 3: Sắp xếp theo kích thước
void sort_size(Image* head) {
    int size = count_nodes(head);                        // B1: đếm số ảnh
    Image** array = malloc(size * sizeof(Image*)); // B2: cấp phát mảng con trỏ

    fill_array(head, array);                             // B3: chuyển linked list thành mảng

    qsort(array, size, sizeof(Image*), compare_by_size); // B4: sắp xếp theo tên
    // Hoặc dùng: compare_by_date nếu muốn sắp theo ngày

    print_sorted_array(array, size);                     // B5: hiển thị danh sách ảnh đã sắp
    pause(); // wait for user read
    free(array);                                         // Giải phóng bộ nhớ
}

// Hàm giúp lựa chọn sort theo cách nào:  sap xep anh theo name, ngay thang, kich thuoc
void sortImage()
{
    int sort_choice;
    printf("Sort by:\n1. Name\n2. Date\n3. Size\n=> ");
    scanf("%d", &sort_choice);
    switch(sort_choice) {
            case 1: sort_name(head);break;
            case 2: sort_date(head); break;
            case 3: sort_size(head); break;
            default: printf("Invalid choice. Try again.\n"); pause(); break;
        }
    

}
   

// thong ke anh theo thang nam
//input: nhap vao khong thoi gian: vd 19.9.2003 -> 21.5.2025
//thong ke ra nhung anh thoa man tieu chi
void static_image_based_on_time() {
    char date_start[11], date_end[11];
    int d1, m1, y1, d2, m2, y2;

    printf("Nhap vao khoang thoi gian can thong ke:\n");
    printf("Date start (DD-MM-YYYY): ");
    scanf(" %10s", date_start);
    printf("Date end   (DD-MM-YYYY): ");
    scanf(" %10s", date_end);

    // Tách ngày tháng năm từ chuỗi
    sscanf(date_start, "%d-%d-%d", &d1, &m1, &y1);
    sscanf(date_end,   "%d-%d-%d", &d2, &m2, &y2);

    Image* current = head;
    int found = 0;

    printf("\nCac anh trong khoang thoi gian %s -> %s:\n", date_start, date_end);

    while (current != NULL) {
        int dc, mc, yc;
        sscanf(current->date, "%d-%d-%d", &dc, &mc, &yc);

        // So sánh năm, tháng, ngày
        int is_after_start =
            (yc > y1) || (yc == y1 && mc > m1) || (yc == y1 && mc == m1 && dc >= d1);
        int is_before_end =
            (yc < y2) || (yc == y2 && mc < m2) || (yc == y2 && mc == m2 && dc <= d2);

        if (is_after_start && is_before_end) {
            printf("- %s | %s | %s | %d KB\n", current->name, current->date, current->description, current->size);
            found = 1;
        }

        current = current->next;
    }

    if (!found) {
        printf("Khong tim thay anh nao trong khoang thoi gian tren.\n");
    }

    pause(); // Dừng màn hình nếu bạn đã định nghĩa hàm pause()
}


//Tim kiem dua tren cac tieu chi: vi du dua vao ten, dua vao ngay chup
//input: lua chonj option name or time, if name -> nhap name, if time -> nhap time
// output: image thoa man tieu chi
void search_advanced()
{
    int search_choice;
    printf("Search by:\n1. Name\n2. Date\n3. Size\n=> ");
    scanf("%d", &search_choice);
    switch(search_choice) {
            // case 1: search_name(head);break;
            // case 2: search_date(head); break;
            // case 3: search_size(head); break;
            default: printf("Invalid choice. Try again.\n"); pause(); break;
        }



}

// xuat file txt: nhap thong tin album anh cua minh ra file txt
void export_file()
{
    FILE* fp = fopen("album.txt", "w");
    if (fp == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    Image* current = head;
    int count = 0;

    fprintf(fp, "THONG TIN ALBUM ANH\n");
    fprintf(fp, "===================\n\n");

    while (current != NULL) {
        fprintf(fp, "Anh %d:\n", ++count);
        fprintf(fp, "Ten anh     : %s\n", current->name);
        fprintf(fp, "Ngay chup   : %s\n", current->date);
        fprintf(fp, "Mo ta       : %s\n", current->description);
        fprintf(fp, "Dung luong  : %d KB\n", current->size);
        fprintf(fp, "---------------------------\n");

        current = current->next;
    }

    fclose(fp);
    printf("Xuat file thanh cong vao 'album.txt'.\n");
    pause(); // nếu bạn đã định nghĩa hàm pause()

}


//dung graph -> luu lien ket giua cac image
// vd cai image 1,4,6 co chung moi lien ket (cung topic, cung ngay, cung thang,...) -> 1 image = 1 node, lien ket 2 node = edge co weight(trong so)

#define MAX_IMAGES 100

int graph[MAX_IMAGES][MAX_IMAGES]; // ma trận trọng số
Image* image_array[MAX_IMAGES];    // để truy cập các ảnh dễ dàng
int image_count = 0;               // số ảnh hiện có

// linked list to mang 2 chieu
void load_images_to_array() {
    Image* temp = head;
    image_count = 0;
    while (temp != NULL && image_count < MAX_IMAGES) {
        image_array[image_count++] = temp;
        temp = temp->next;
    }
}

int calculate_weight(Image* a, Image* b) {
    int weight = 0;

    if (strcmp(a->date, b->date) == 0)
        weight += 3;  // cùng ngày thì trọng số cao hơn
    else {
        // kiểm tra cùng tháng-năm
        int day1, month1, year1;
        int day2, month2, year2;
        sscanf(a->date, "%d-%d-%d", &day1, &month1, &year1);
        sscanf(b->date, "%d-%d-%d", &day2, &month2, &year2);

        if (month1 == month2 && year1 == year2)
            weight += 2;  // cùng tháng năm
        else if (year1 == year2)
            weight += 1;  // cùng năm
    }

    // Nếu mô tả giống nhau (đơn giản kiểm tra chuỗi giống hệt)
    if (strcmp(a->description, b->description) == 0)
        weight += 2;

    return weight;
}



void create_relation_graph() {
    load_images_to_array(); // đưa danh sách ảnh sang mảng

    for (int i = 0; i < image_count; i++) {
        for (int j = 0; j < image_count; j++) {
            if (i != j) {
                graph[i][j] = calculate_weight(image_array[i], image_array[j]);
            } else {
                graph[i][j] = 0; // không nối chính nó
            }
        }
    }

    printf("Do thi lien ket da duoc tao.\n");

    printf("\nMa tran trong so giua cac anh:\n\n");

    // In tiêu đề cột
    printf("%15s", ""); // để lệch ô đầu
    for (int i = 0; i < image_count; i++) {
        printf("%15s", image_array[i]->name);
    }
    printf("\n");

    // In dòng kẻ ngang cho đẹp
    printf("%15s", "");
    for (int i = 0; i < image_count; i++) {
        printf("---------------");
    }
    printf("\n");

    // In các hàngadd
    for (int i = 0; i < image_count; i++) {
        printf("%15s", image_array[i]->name); // tên hàng, in 15 ki tu, can phai
        for (int j = 0; j < image_count; j++) {
            printf("%15d", graph[i][j]);
        }
        printf("\n");
    }
    pause();
}




// Menu chính
void showMenu() {
    int choice;
    do {
        clearScreen();
        printf("====== Photo Album Manager ======\n");
        printf("1. Add Photo\n");
        printf("2. Add auto 10 Photos\n");
        printf("3. Delete Photo\n");
        printf("4. Search Photo\n");
        printf("5. Edit Photo\n");
        printf("6. Display All Photos\n");
        printf("7. Detect Duplicates\n");
        printf("More advanced function: \n");
        printf("8. Sort Image based on Name, Date,...\n");
        printf("9. Create relation graph\n");
        printf("0. Exit\n");
        printf("=> Your choice: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice) {
            case 1: addPhoto(); break;
            case 2: addPhoto_auto(); break;
            case 3: deletePhoto(); break;
            case 4: searchPhoto(); break;
            case 5: editPhoto(); break;
            case 6: displayPhotos(); break;
            case 7: detectDuplicates(); break;
            case 8: sortImage(); break;
            case 9: create_relation_graph(); break;
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
