#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

struct document get_document(char* text) {
  struct word* words = calloc(1000, sizeof(struct word));
  struct sentence* sentences = calloc(500, sizeof(struct sentence));
  struct paragraph* paragraphs = calloc(5, sizeof(struct paragraph));
  struct document doc;
  doc.data = paragraphs;
  doc.paragraph_count = 0;

  int wordIndex = 0, sentIndex = 0, parIndex = 0;

  words[0].data = text;
  sentences[0].data = &words[0];
  sentences[0].word_count = 0;
  paragraphs[0].data = &sentences[0];
  paragraphs[0].sentence_count = 0;
  doc.paragraph_count = 0;

  while (*text > 0) {
    switch (*text) {
      case 32: // space
        *text = 0;

        wordIndex += 1;
        words[wordIndex].data = text + 1;
        sentences[sentIndex].word_count += 1;
        break;
      case 46: // period
        *text = 0;

        wordIndex += 1;
        words[wordIndex].data = text + 1;
        sentences[sentIndex].word_count += 1;

        sentIndex += 1;
        sentences[sentIndex].data = words + wordIndex;
        paragraphs[parIndex].sentence_count += 1;
        break;
      case 10: // newline
        *text = 0;

        /*wordIndex += 1;*/
        words[wordIndex].data = text + 1;
        /*sentences[sentIndex].word_count += 1;*/

        /*sentIndex += 1;*/
        sentences[sentIndex].data = words + wordIndex;
        /*paragraphs[parIndex].sentence_count += 1;*/

        parIndex += 1;
        paragraphs[parIndex].data = sentences + sentIndex;
        doc.paragraph_count += 1;
        break;
    }
    text += 1;
  }
  doc.paragraph_count += 1;

  /*
  for (int i = 0; i < wordIndex; i++) {
    printf("Word %d: %s\n", i, words[i].data);
  }

  printf("Paragraph index: %d\n", parIndex);
  for (int i = 0; i < sentIndex; i++) {
    printf("Sentence %d: wc=%d, starts with %s\n", i, sentences[i].word_count, sentences[i].data[0]);
  }

  for (int i = 0; i < parIndex + 1; i++) {
    printf("Paragraph %d: sc=%d, starts with %s\n", i, doc.data[i].sentence_count, doc.data[i].data[0].data[0]);
  }
  printf("Paragraph count = %d\n", doc.paragraph_count);
  */
  return doc;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
  return Doc.data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
  return kth_paragraph(Doc,m).data[k - 1];
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
  return kth_sentence_in_mth_paragraph(Doc, m, n).data[k - 1];
}

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
