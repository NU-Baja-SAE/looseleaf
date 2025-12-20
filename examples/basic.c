#include <looseleaf.h>

#define SIZE 4096

int main() {
  char arena[SIZE];
  ll_Context* ctx = ll_init(arena, SIZE);
  ll_begin(ctx);

  ll_NodeHandle im = ll_image(NULL, {.width = 1, .height = 1});

  // nesting multiple node combinators
  ll_NodeHandle overlay_demo = ll_overlay(
    {.align_h = LL_HORIZ_ALIGN_LEFT},
    ll_text({.letter_spacing = 3}, "hello world"),
    ll_beside({.align_v = LL_VERT_ALIGN_CENTER}, im, im)
  );

  // will draw something like this...

  // +----------+----------+
  // |          |          |
  // hello, world!         |
  // |          |          |
  // +----------+----------+

  // folding over an array
  const char *messages[3];
  messages[0] = "zero";
  messages[1] = "one";
  messages[2] = "two";
  ll_NodeHandle align_demo = LL_FOLDL1(ll_above, {.align_h = LL_HORIZ_ALIGN_RIGHT}, messages);

  // will draw something like this...

  //  zero
  //   one
  //   two

  ll_NodeHandle complete_demo = ll_overlay(
    {.align_h = LL_HORIZ_ALIGN_RIGHT, .align_v = LL_VERT_ALIGN_BOTTOM},
    align_demo,
    overlay_demo
  );

  // will draw something like this...

  // +----------+----------+
  // |          |          |
  // hello, world!      zero
  // |          |        one
  // +----------+--------two

  ll_RenderCommandArray cmds = ll_gen_commands(complete_demo);
}
