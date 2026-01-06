#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PLANET_COUNT 8
#define PI 3.14159265359

// Fonksiyon Prototipleri
void show_menu();
double get_positive_input(char *message);
void wait_for_user();

// Deney Fonksiyonlari
void exp_free_fall(double *g_ptr, char **names_ptr);
void exp_vertical_throw(double *g_ptr, char **names_ptr);
void exp_weight(double *g_ptr, char **names_ptr);
void exp_potential_energy(double *g_ptr, char **names_ptr);
void exp_hydrostatic_pressure(double *g_ptr, char **names_ptr);
void exp_buoyancy(double *g_ptr, char **names_ptr);
void exp_pendulum(double *g_ptr, char **names_ptr);
void exp_rope_tension(double *g_ptr, char **names_ptr);
void exp_elevator(double *g_ptr, char **names_ptr);

int main() {
    // Gezegen yercekimi ivmeleri (Merkur, Venus, Dunya, Mars, Jupiter, Saturn, Uranus, Neptun)
    double gravities[PLANET_COUNT] = {3.70, 8.87, 9.81, 3.71, 24.79, 10.44, 8.69, 11.15};
    
    // Gezegen isimleri
    char *planet_names[PLANET_COUNT] = {
        "Merkur", "Venus", "Dunya", "Mars", 
        "Jupiter", "Saturn", "Uranus", "Neptun"
    };

    char scientist_name[50];
    int choice;

    // 1. Program Açılışı
    printf("************************************************\n");
    printf("* UZAY SIMULASYONUNA HOS GELDINIZ        *\n");
    printf("************************************************\n");
    printf("Lutfen Bilim Insani Adini Giriniz: ");
    // Bosluklu isim alabilmek icin fgets kullaniyoruz
    fgets(scientist_name, 50, stdin);
    // Sondaki enter karakterini silme islemi
    scientist_name[strcspn(scientist_name, "\n")] = 0;

    printf("\nHos geldin, Bilim Insani %s.\n", scientist_name);
    printf("Simulasyon sistemi baslatiliyor...\n");

    while (1) {
        show_menu();
        printf("\nLutfen yapmak istediginiz deneyi secin (-1 Cikis): ");
        if (scanf("%d", &choice) != 1) {
            // Harf girilirse sonsuz donguye girmemesi icin buffer temizleme
            while(getchar() != '\n'); 
            choice = 0; // Gecersiz secim
        }

        if (choice == -1) {
            printf("\nSimulasyon sonlandiriliyor. Iyi calismalar %s!\n", scientist_name);
            break;
        }

        printf("\n------------------------------------------------\n");
        printf("Secilen Deney Numarasi: %d\n", choice);
        printf("Bilim Insani: %s\n", scientist_name);
        printf("------------------------------------------------\n");

        switch (choice) {
            case 1: exp_free_fall(gravities, planet_names); break;
            case 2: exp_vertical_throw(gravities, planet_names); break;
            case 3: exp_weight(gravities, planet_names); break;
            case 4: exp_potential_energy(gravities, planet_names); break;
            case 5: exp_hydrostatic_pressure(gravities, planet_names); break;
            case 6: exp_buoyancy(gravities, planet_names); break;
            case 7: exp_pendulum(gravities, planet_names); break;
            case 8: exp_rope_tension(gravities, planet_names); break;
            case 9: exp_elevator(gravities, planet_names); break;
            default:
                printf("Gecersiz bir secim yaptiniz! Lutfen tekrar deneyin.\n");
        }
        
        wait_for_user();
    }

    return 0;
}

// Menuyu ekrana basan fonksiyon
void show_menu() {
    printf("\n================ DENEY LISTESI ================\n");
    printf("1. Serbest Dusme Deneyi\n");
    printf("2. Yukari Atis Deneyi\n");
    printf("3. Agirlik Deneyi\n");
    printf("4. Kutlecekimsel Potansiyel Enerji Deneyi\n");
    printf("5. Hidrostatik Basinc Deneyi\n");
    printf("6. Arsimet Kaldirma Kuvveti Deneyi\n");
    printf("7. Basit Sarkac Periyodu Deneyi\n");
    printf("8. Sabit Ip Gerilmesi Deneyi\n");
    printf("9. Asansor Deneyi\n");
    printf("============================================\n");
}

// Kullanicidan pozitif deger alma ve ternary operator zorunlulugu fonksiyonu
double get_positive_input(char *message) {
    double val;
    printf("%s", message);
    scanf("%lf", &val);
    
    // ZORUNLULUK: if kullanmadan ternary ile mutlak deger alma
    double final_val = (val < 0) ? -val : val;
    
    if (val < 0) {
        printf("UYARI: Negatif deger girildi! Mutlak degeri (%0.2f) baz alinacaktir.\n", final_val);
    }
    return final_val;
}

// Cikti okumak icin bekletme
void wait_for_user() {
    printf("\nDevam etmek icin Enter'a basin...");
    while(getchar() != '\n'); // Onceki buffer'i temizle
    getchar(); // Bekle
}

// --- DENEY FONKSIYONLARI ---

// 1. Serbest Dusme: h = 0.5 * g * t^2
void exp_free_fall(double *g_ptr, char **names_ptr) {
    double t = get_positive_input("Sureyi giriniz (sn): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Dusulen Mesafe (m)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        // ZORUNLULUK: Pointer aritmetigi ile diziye erisim
        double g = *(g_ptr + i);
        double h = 0.5 * g * t * t;
        printf("%-10s | %0.2f m\n", *(names_ptr + i), h);
    }
}

// 2. Yukari Atis: h_max = v0^2 / (2g)
void exp_vertical_throw(double *g_ptr, char **names_ptr) {
    double v0 = get_positive_input("Firlatma hizini giriniz (m/s): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Maks. Yukseklik (m)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double h_max = (v0 * v0) / (2 * g);
        printf("%-10s | %0.2f m\n", *(names_ptr + i), h_max);
    }
}

// 3. Agirlik: G = m * g
void exp_weight(double *g_ptr, char **names_ptr) {
    double m = get_positive_input("Cismin kutlesini giriniz (kg): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Agirlik (N)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double weight = m * g;
        printf("%-10s | %0.2f N\n", *(names_ptr + i), weight);
    }
}

// 4. Potansiyel Enerji: Ep = m * g * h
void exp_potential_energy(double *g_ptr, char **names_ptr) {
    double m = get_positive_input("Cismin kutlesini giriniz (kg): ");
    double h = get_positive_input("Yuksekligi giriniz (m): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Potansiyel Enerji (J)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double ep = m * g * h;
        printf("%-10s | %0.2f J\n", *(names_ptr + i), ep);
    }
}

// 5. Hidrostatik Basinc: P = rho * g * h
void exp_hydrostatic_pressure(double *g_ptr, char **names_ptr) {
    double rho = get_positive_input("Sivinin yogunlugunu giriniz (kg/m^3): ");
    double h = get_positive_input("Derinligi giriniz (m): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Basinc (Pa)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double p = rho * g * h;
        printf("%-10s | %0.2f Pa\n", *(names_ptr + i), p);
    }
}

// 6. Arsimet Kaldirma Kuvveti: Fk = rho * g * V
void exp_buoyancy(double *g_ptr, char **names_ptr) {
    double rho = get_positive_input("Sivinin yogunlugunu giriniz (kg/m^3): ");
    double V = get_positive_input("Batan hacmi giriniz (m^3): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Kaldirma Kuvveti (N)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double fk = rho * g * V;
        printf("%-10s | %0.2f N\n", *(names_ptr + i), fk);
    }
}

// 7. Basit Sarkac Periyodu: T = 2 * PI * sqrt(L / g)
void exp_pendulum(double *g_ptr, char **names_ptr) {
    double L = get_positive_input("Sarkac uzunlugunu giriniz (m): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Periyot (s)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double T = 2 * PI * sqrt(L / g);
        printf("%-10s | %0.2f s\n", *(names_ptr + i), T);
    }
}

// 8. Sabit Ip Gerilmesi: T = m * g
void exp_rope_tension(double *g_ptr, char **names_ptr) {
    double m = get_positive_input("Asili cismin kutlesini giriniz (kg): ");
    
    printf("\n%-10s | %-20s\n", "Gezegen", "Ip Gerilmesi (N)");
    printf("--------------------------------\n");
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double t = m * g;
        printf("%-10s | %0.2f N\n", *(names_ptr + i), t);
    }
}

// 9. Asansor Deneyi: N = m(g + a) veya N = m(g - a)
void exp_elevator(double *g_ptr, char **names_ptr) {
    double m = get_positive_input("Cismin kutlesini giriniz (kg): ");
    double a = get_positive_input("Asansorun ivmesini giriniz (m/s^2): ");
    
    printf("\nAsansorun Hareket Yonu:\n");
    printf("1. Yukari Hizlanan veya Asagi Yavaslayan (+ ivme etkisi)\n");
    printf("2. Asagi Hizlanan veya Yukari Yavaslayan (- ivme etkisi)\n");
    
    int type;
    printf("Durumu seciniz (1 veya 2): ");
    scanf("%d", &type);

    printf("\n%-10s | %-20s\n", "Gezegen", "Hissedilen Agirlik (N)");
    printf("--------------------------------\n");

    for (int i = 0; i < PLANET_COUNT; i++) {
        double g = *(g_ptr + i);
        double N;
        
        if (type == 1) {
            N = m * (g + a); // Formu: 9
        } else {
            N = m * (g - a); // Formul: 9.1
            // Agirlik negatif olamaz (yercekiminden hizli duserse tavana yapisir, 0 alinabilir veya mutlak)
            // Fiziksel olarak ip kopmasi vs yoksa tavana dogru kuvvet uygular. 
            // Ancak basitlik adina ternary ile mutlak alalim.
            N = (N < 0) ? -N : N; 
        }
        
        printf("%-10s | %0.2f N\n", *(names_ptr + i), N);
    }
}