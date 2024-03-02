/*
 * page svg from text
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _pvg_page_h
#define _pvg_page_h

#define pvg_page_lh 18
#define pvg_page_em 6
#define pvg_page_x0 30
#define pvg_page_y0 50

static const char *page_head[] = {
  "<?xml version=\"1.0\" standalone=\"no\"?>",
  "<?xml-stylesheet href=\"https://cdn.jsdelivr.net/gh/aaaakshat/cm-web-fonts@latest/fonts.css\" type=\"text/css\"?>",
  "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">",
  "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"500\" height=\"500\" viewBox=\"0 0 500 500\">",
  "  <defs>",
  "    <style type=\"text/css\">",
  "      text.rm {",
  "	  font-family: \"Computer Modern Serif\", serif;",
  "	  font-size: 12;",
  "	  fill: black;",
  "      }",
  "      text.tt {",
  "	  font-family: \"Computer Modern Typewriter\", monospace;",
  "	  font-size: 10;",
  "	  fill: black;",
  "      }",
  "      text.ti {",
  "	  font-size: 22;",
  "	  font-weight: bold",
  "      }",
  "      text.ln {",
  "          fill: #0066B3",
  "      }",
  "    </style>",
  "  </defs>",
  "  <rect x=\"0\" y=\"0\" width=\"500\" height=\"500\" fill=\"#FFF\" stroke=\"#000\" stroke-width=\"30\" />",
};
static const uint32_t page_head_count = 26;
static const char *page_tail[] = {
  "</svg>",
};
static const uint32_t page_tail_count = 1;

#endif
