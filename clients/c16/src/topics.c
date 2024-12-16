/**
 * @brief   FujiNet News Reader - Commodore 16 Version
 * @author  Thomas Cherryhomes
 * @license gpl v. 3
 * @brief   topics
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <c16.h>
#include <conio.h>
#include "topics.h"

extern State state;

const char *topic_names[9]=
  {
    " TOP STORIES",
    " WORLD NEWS",
    " BUSINESS",
    " SCIENCE",
    " TECHNOLOGY",
    " HEALTH ",
    " ENTERTAINMENT",
    " POLITICS",
    " SPORTS"
  };

unsigned char selected_topic;

void topics_header(void)
{
  gotoxy(0,0);
  textcolor(BCOLOR_GREEN|CATTR_LUMA3);
  cprintf(TOPICS_TOP);
  textcolor(BCOLOR_WHITE|CATTR_LUMA7);
}

void topics_footer(void)
{
  gotoxy(0,24);
  textcolor(BCOLOR_GREEN|CATTR_LUMA3);
  cprintf(TOPICS_BOT);
  textcolor(BCOLOR_BLUE|CATTR_LUMA7);
}

void topics_menu(void)
{
  unsigned char i;

  gotoxy(0,TOPICS_Y);
  
  for (i=0;i<9;i++)
    {
      revers(i==selected_topic ? 1 : 0);
      cprintf("%-40s\r\n",topic_names[i]);
    }
  
  revers(0);
}

State topics(void)
{
  clrscr();
  cbm_k_bsout(0x0E); // Go upper/lower charset

  bordercolor(BCOLOR_GREEN|CATTR_LUMA3);
  textcolor(BCOLOR_WHITE|CATTR_LUMA7);
  bgcolor(BCOLOR_GREEN|CATTR_LUMA1);
  revers(1);

  topics_header();
  topics_footer();

  revers(0);

  while (state==TOPICS)
    {
      topics_menu();
      switch(cgetc())
	{
	case CH_DOWN:
	  ( selected_topic < TOPICS_MAX - 1 ? selected_topic++ : selected_topic);
	  break;
	case CH_UP:
	  ( selected_topic ? selected_topic-- : selected_topic );
	  break;
	case CH_RETURN:
	  state=TITLES;
	  break;
	}
    }
  
  return TITLES;
}
