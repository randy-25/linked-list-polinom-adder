/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 6 - Linked List
 *   Hari dan Tanggal    : Kamis, 18 April 2024
 *   Nama (NIM)          : Randy Revaldo Pratama (13222012)
 *   Nama File           : main.c
 *   Deskripsi           : Membuat fungsi penjumlahan dan sorting polinomial
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct polinomial {
    int coef;
    int power;
    struct polinomial* next;
} polinomial;

/**
 * Fungsi pengisian linked list polinomial (tidak boleh diubah)
*/
void fill(polinomial* bilangan, int size, int* arr_coef, int* arr_power) {
    polinomial* temp = bilangan;
    bilangan->coef = arr_coef[0];
    bilangan->power = arr_power[0];

    for (int i = 1; i<size; i++) {
        temp->next = (polinomial *) malloc (sizeof(polinomial));
        temp = temp->next;
        temp->coef = arr_coef[i];
        temp->power = arr_power[i];
    }
    temp->next = NULL;

    return;
}

/**
 * Fungsi untuk print isi polinomial (tidak boleh diubah, gunakan untuk membantu debugging)
*/
void show(polinomial* bilangan) {
    while (bilangan->next != NULL) {
        printf("%dx^%d, ", bilangan->coef, bilangan->power);
        bilangan = bilangan->next;
    }
    printf("%dx^%d\n", bilangan->coef, bilangan->power);

    return;
}

/**
 * Fungsi untuk menjumlahkan dua buah polinomial
 * @param bilangan_1 bilangan polinomial pertama
 * @param bilangan_2 bilangan polinomial kedua
 * @return hasil penjumlahan
*/

polinomial* add(polinomial* bilangan_1, polinomial *bilangan_2) {
    // Implementasikan kodemu
    polinomial* temp1 = (polinomial*) malloc (sizeof(polinomial));
    temp1->coef = bilangan_1->coef;
    temp1->power = bilangan_1->power;
    temp1->next = bilangan_1->next;
    
    //Menyimpan lokasi head
    polinomial* sum = (polinomial*) malloc (sizeof(polinomial));
    sum->coef = temp1->coef;
    sum->power = temp1->power;
    sum->next = temp1->next;

    // Melihat jika power head akan ada yang sama dengan power yang dijumlah
    polinomial* temp2Head = (polinomial*) malloc (sizeof(polinomial));
    temp2Head->coef = bilangan_2->coef;
    temp2Head->power = bilangan_2->power;
    temp2Head->next = bilangan_2->next; 
    while(temp2Head->next != NULL){
        if (sum->power == temp2Head->power){
            sum->coef = sum->coef + temp2Head->coef;
        }
        temp2Head = temp2Head->next;
    }

    int trackInsert = 0;
    int *insert_coef = NULL;
    int *insert_power = NULL;

    int temp1_count = 0;
    int *temp1_coef = (int*)malloc(temp1_count*sizeof(int));
    int *temp1_power = (int*)malloc(temp1_count*sizeof(int));

    int temp2_count = 0;
    int *temp2_coef = (int*)malloc(temp2_count*sizeof(int));
    int *temp2_power = (int*)malloc(temp2_count*sizeof(int));

    while (temp1 != NULL){
        polinomial* temp2 = (polinomial*) malloc (sizeof(polinomial));
        temp2->coef = bilangan_2->coef;
        temp2->power = bilangan_2->power;
        temp2->next = bilangan_2->next;
        while(temp2 != NULL){
            if (temp1->power == temp2->power){
                temp1->coef = temp1->coef + temp2->coef;
            }
            temp2 = temp2->next;
        }
        //mengambil pangkat dan koef dari bilangan 1
        temp1_count += 1;
        temp1_coef = (int *) realloc(temp1_coef, temp1_count * sizeof(int));
        temp1_power = (int *) realloc(temp1_power, temp1_count * sizeof(int));
        temp1_coef[temp1_count-1] = temp1->coef;
        temp1_power[temp1_count-1] = temp1->power;
        temp1 = temp1-> next;  
        if (temp1 ==NULL){
            break;
        }
    }

    //mengambil pangkat dan koef dari bilangan 2
    polinomial* temp2 = (polinomial*) malloc (sizeof(polinomial));
    temp2->coef = bilangan_2->coef;
    temp2->power = bilangan_2->power;
    temp2->next = bilangan_2->next;
    while(temp2 != NULL){
        temp2_count += 1;
        temp2_coef = (int *) realloc(temp2_coef, temp2_count * sizeof(int));
        temp2_power = (int *) realloc(temp2_power, temp2_count * sizeof(int));
        temp2_coef[temp2_count-1] = temp2->coef;
        temp2_power[temp2_count-1] = temp2->power;
        temp2 = temp2->next;
    }

    // memasukkan pangkat dan koef jika bilangan 1 dan 2 berbeda
    for(int j = 0; j<temp2_count; j++){
        int count = 0;
        for(int i = 0; i < temp1_count; i++){            
            if (temp2_power[j] != temp1_power[i]){
                count++;
            }
        }
        if (count == temp1_count){
            trackInsert += 1;
            insert_coef = (int *) realloc(insert_coef, trackInsert * sizeof(int));
            insert_power = (int *) realloc(insert_power, trackInsert * sizeof(int));
            insert_coef[trackInsert-1] = temp2_coef[j];
            insert_power[trackInsert-1] = temp2_power[j];
        }
    }

    if(trackInsert != 0){
        polinomial *pInsert = (polinomial *) malloc(sizeof(polinomial));
        fill(pInsert,trackInsert,insert_coef,insert_power); //membuat linked list berisi pangkat yang beda
        polinomial* lastTemp = sum;
        while(lastTemp->next != NULL){
            lastTemp = lastTemp->next;
        }
        lastTemp->next = pInsert;
    }
    return sum;
}

/**
 * Fungsi untuk mengurutkan elemen polinomial
 * @param bilangan bilangan yang ingin diurutkan
 * @return hasil pengurutan
*/

polinomial* sort(polinomial* bilangan) {
    // Implementasikan kodemu

    int temp_count = 0;
    int *temp_coef = (int*)malloc(temp_count*sizeof(int));
    int *temp_power = (int*)malloc(temp_count*sizeof(int));

    polinomial* temp = (polinomial*) malloc (sizeof(polinomial));
    temp->coef = bilangan->coef;
    temp->power = bilangan->power;
    temp->next = bilangan->next;
    while(temp != NULL){
        temp_count += 1;
        temp_coef = (int *) realloc(temp_coef, temp_count * sizeof(int));
        temp_power = (int *) realloc(temp_power, temp_count * sizeof(int));
        temp_coef[temp_count-1] = temp->coef;
        temp_power[temp_count-1] = temp->power;
        temp = temp->next;
    }

    int temporary; // temp variable sebagai penyimpan sementara
    // sorting menggunakan bubble sort
    for(int i = 0; i < temp_count; i++) {
        for(int j = 0; j < temp_count - 1; j++) {
            if(temp_power[j] > temp_power[j + 1]) {
                temporary = temp_power[j];
                temp_power[j] = temp_power[j + 1];
                temp_power[j + 1] = temporary;

                temporary = temp_coef[j];
                temp_coef[j] = temp_coef[j + 1];
                temp_coef[j + 1] = temporary;
            }
        }
    }

    polinomial *pSorted = (polinomial *) malloc(sizeof(polinomial));
    fill(pSorted,temp_count,temp_coef,temp_power);
    bilangan = pSorted; 

}

int main() {
    // Inisialisasi polinomial untuk test case
    polinomial *p1 = (polinomial *) malloc(sizeof(polinomial));
    polinomial *p2 = (polinomial *) malloc(sizeof(polinomial));

    // Isi nilai polinomial 1
    int p1_coef[5] = {1, 2, 3, 4, 2};
    int p1_power[5] = {3, 2, 1, 4, 6};
    fill(p1, 5, p1_coef, p1_power);
    // show(p1);
    
    // Isi nilai polinomial 2
    int p2_coef[2] = {3, 11};
    int p2_power[2] = {3, 11};
    fill(p2, 2, p2_coef, p2_power);
    // show(p2);


    // Input opsi test case
    int opsi;
    printf("Masukkan testcase: ");
    scanf("%d", &opsi);

    polinomial* operasi;
    polinomial* operasi_sorted;
    if (opsi == 0) {
        operasi = add(p2, p1);
        operasi_sorted = sort(operasi);
        show(operasi_sorted);
    }
    else if (opsi == 1) {
        operasi = add(p1, p2);
        operasi_sorted = sort(operasi);
        show(operasi_sorted);
    }
    else if (opsi == 2) {
        operasi = add(p1, p1);
        operasi_sorted = sort(operasi);
        show(operasi_sorted);
    }
    else if (opsi == 3) {
        operasi = add(p2, p2);
        operasi_sorted = sort(operasi);
        show(operasi_sorted);
    }
    else if (opsi == 4) {
        operasi = add(p1, p1);
        operasi = add(p2, operasi);
        operasi_sorted = sort(operasi);
        show(operasi_sorted);
    }
}
