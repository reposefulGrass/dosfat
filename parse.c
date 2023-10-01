
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct boot_block {
    uint8_t bootstrap_program_part[3];
    uint8_t manufacturer_description[8];
    uint8_t num_bytes_per_block[2];
    uint8_t num_blocks_per_alloc_uint[1];
    uint8_t num_reserved_blocks[2];
    uint8_t num_file_alloc_tables[1];
    uint8_t num_root_dir_entries[2];
    uint8_t num_total_blocks_small[2];
    uint8_t media_descriptor[1];
    uint8_t num_blocks_per_file_alloc_tables[2];
    uint8_t num_blocks_per_track[2];
    uint8_t num_heads[2];
    uint8_t num_hidden_blocks[4];
    uint8_t num_total_blocks_big[4];
    uint8_t physical_drive_num[2];
    uint8_t extended_boot_record_signature[1];
    uint8_t volume_serial_number[4];
    uint8_t volume_label[11];
    uint8_t file_system_identifier[8];
    uint8_t remainder[0x1c0]; 
    uint8_t boot_block_signature[2];  
};
typedef struct boot_block boot_block_t;


boot_block_t
boot_block_parse (uint8_t *raw_bytes, uint32_t size) {
    assert(size == sizeof(boot_block_t));

    boot_block_t bb;          
    memcpy(&bb, raw_bytes, size);
    return bb;
}


int
main (int argc, char **argv) {
    uint8_t *raw_bytes = malloc(sizeof(boot_block_t));
    raw_bytes[0] = 0x01;
    raw_bytes[1] = 0x02;
    raw_bytes[2] = 0x03;

    boot_block_t bb = boot_block_parse(raw_bytes, 512); 
    printf(
        "Bootstrap Program Part: [%x %x %x]\n", 
        bb.bootstrap_program_part[0],
        bb.bootstrap_program_part[1],
        bb.bootstrap_program_part[2]
    );
    
    return EXIT_SUCCESS;
}
