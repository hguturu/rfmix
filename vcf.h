#ifndef VCF_H
#define VCF_H

#include <stdint.h>
#include "genetic-map.h"
#include "inputline.h"
#include "hash-table.h"

typedef struct {
  int sample_idx;
  int column_idx;
  char *sample_id;
  int8_t *haplotypes[2];
} sample_t;

typedef struct {
  int pos;
  double genetic_pos;
  char *snp_id;
  char *ref;
  char *alt;
} snp_t;

#define ALLELE_ALLOC_STEP (16)
class VCF {
 public:
  VCF(char *fname, char *chm);
  ~VCF();

  void load_snps(char *chromosome, GeneticMap *genetic_map);
  int8_t *get_haplotype(char *sample_id);
  void load_haplotypes(char *chromosome);

  sample_t *samples;
  int n_samples;

  snp_t *snps;
  int n_snps;

  static char *find_allele_string(char *q);
  static int n_alleles;
  static char **alleles;

 private:
  char *fname;
  sample_t **column_map;
  int n_columns;
  HashTable *sample_map;
  Inputline *f;
  void parse_samples(char *sample_line);

};

#define VCF_LEAD_COLS (9)
#define SAMPLE_ALLOC_STEP (256)
#define SNP_ALLOC_STEP (16384)


#endif
