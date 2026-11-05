/**
 * @file  test_game.c
 * @brief Unit test logic game - chay tren PC, KHONG can kit.
 * @owner DEV 2 - nhanh feature/task-game
 *
 * Chay:  make test
 *
 * TAI SAO TEST DUOC TREN PC:
 *   Ba ham duoi trong task_game.c khong goi ham HAL nao va khong dung
 *   bien toan cuc. Nen bien dich lai bang gcc x86 la chay duoc ngay,
 *   khong can nap len board - vong lap sua loi nhanh hon nhieu.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "app_types.h"

/* Khai bao lai - test bien dich truc tiep phan logic, khong link ca task */
bool     game_aabb_overlap(const entity_t *a, const entity_t *b);
uint16_t game_score_for_kill(uint8_t wave);
void     game_wave_params(uint8_t wave, uint8_t *out_count, int16_t *out_speed);

static int g_pass = 0, g_fail = 0;

#define CHECK(cond, name)                                        \
    do {                                                         \
        if (cond) {                                              \
            g_pass++;                                            \
            printf("  [ OK ] %s\n", name);                       \
        } else {                                                 \
            g_fail++;                                            \
            printf("  [FAIL] %s  (dong %d)\n", name, __LINE__);  \
        }                                                        \
    } while (0)

static entity_t mk(int16_t px, int16_t py, uint8_t w, uint8_t h)
{
    entity_t e;
    memset(&e, 0, sizeof(e));
    e.x = TO_FIXED(px);
    e.y = TO_FIXED(py);
    e.w = w;
    e.h = h;
    e.alive = true;
    return e;
}

static void test_aabb(void)
{
    printf("game_aabb_overlap:\n");

    entity_t a = mk(10, 10, 8, 8);

    entity_t trung_hoan_toan = mk(10, 10, 8, 8);
    CHECK(game_aabb_overlap(&a, &trung_hoan_toan), "hai hop trung nhau");

    entity_t cham_goc = mk(17, 17, 8, 8);
    CHECK(game_aabb_overlap(&a, &cham_goc), "cham nhau o goc");

    entity_t tach_ngang = mk(30, 10, 8, 8);
    CHECK(!game_aabb_overlap(&a, &tach_ngang), "tach xa theo chieu ngang");

    entity_t tach_doc = mk(10, 30, 8, 8);
    CHECK(!game_aabb_overlap(&a, &tach_doc), "tach xa theo chieu doc");

    entity_t sat_canh = mk(18, 10, 8, 8);
    CHECK(!game_aabb_overlap(&a, &sat_canh), "sat canh nhung chua cham");

    entity_t nam_trong = mk(12, 12, 2, 2);
    CHECK(game_aabb_overlap(&a, &nam_trong), "hop nho nam gon ben trong");
}

static void test_score(void)
{
    printf("game_score_for_kill:\n");

    CHECK(game_score_for_kill(1) > 0U, "dot 1 phai co diem");
    CHECK(game_score_for_kill(2) >= game_score_for_kill(1), "dot sau khong thap hon");
    CHECK(game_score_for_kill(3) > game_score_for_kill(1), "dot 3 cao hon dot 1");
}

static void test_wave(void)
{
    printf("game_wave_params:\n");

    uint8_t c1 = 0, c3 = 0;
    int16_t s1 = 0, s3 = 0;

    game_wave_params(1, &c1, &s1);
    game_wave_params(3, &c3, &s3);

    CHECK(c1 > 0U && c1 <= MAX_ENEMIES, "so ga dot 1 nam trong gioi han");
    CHECK(c3 > 0U && c3 <= MAX_ENEMIES, "so ga dot 3 nam trong gioi han");
    CHECK(c3 >= c1, "dot 3 khong it ga hon dot 1");
    CHECK(s3 >= s1, "dot 3 khong cham hon dot 1");
}

int main(void)
{
    printf("\n=== Unit test logic game ===\n\n");

    test_aabb();
    test_score();
    test_wave();

    printf("\nKet qua: %d dat, %d truot\n\n", g_pass, g_fail);
    return (g_fail == 0) ? 0 : 1;
}
