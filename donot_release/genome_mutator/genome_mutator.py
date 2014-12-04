from Bio import SeqIO
from random import randint
import sys
import io


if(len(sys.argv)!=8):
    print "usage = python "+sys.argv[0]+" [input sequence file (a unique sequence)] [output file name] [log fasta file] [nb insertions] [min size insertion] [max size insertion] [nb_snps]"
    sys.exit(0)

my_input=sys.argv[1]
my_output=sys.argv[2]
my_log=sys.argv[3]
print "#input = "+my_input
print "#output = "+my_output
print "#logfile = "+my_log


nb_insertions=int(sys.argv[4])
min_size_insertions=int(sys.argv[5])
max_size_insertions=int(sys.argv[6])

nb_snps=int(sys.argv[7])

print "#nb_insertions = "+str(nb_insertions)
print "#min_size_insertions = "+str(min_size_insertions)
print "#max_size_insertions = "+str(max_size_insertions)
print "#nb_snps "+str(nb_snps)

sys.stdout = open(my_log, 'w') # all incoming stuffs are written in the log file

def int2nuc(value):
    if value%4==0: return 'A'
    if value%4==1: return 'C'
    if value%4==2: return 'G'
    return 'T'
    

def random_dna_sequence(size):
    seq=""
    for i in range(size): seq+=int2nuc(randint(0,4))
    return seq

    
def mutate(nuclotide):
    while True:
        mutated=random_dna_sequence(1)
        if mutated!=nuclotide:
            return mutated

def reverse_numeric(x, y):
    return y - x


size_neighbor=20

for seq_record in SeqIO.parse(my_input, "fasta"):
    limit=len(seq_record.seq)
    

    positions = [0]*nb_snps
    for i in range(nb_snps): positions[i]=randint(0,limit)
    positions = sorted(positions) # cuter
    for snp_id in range(nb_snps):
        pos = positions[snp_id]
        init=seq_record.seq[pos]
        mutated=mutate(init)
        comment=">SNP_"+str(snp_id)+"|upper|"+str(pos)+"|"+init+"/"+mutated
        sequence=seq_record.seq[pos-size_neighbor:pos+size_neighbor]
        print comment              
        print sequence
        comment=">SNP_"+str(snp_id)+"|lower|"+str(pos)+"|"+init+"/"+mutated
        seq_record.seq=seq_record.seq[0:pos]+mutated+seq_record.seq[pos+1:]
        sequence=seq_record.seq[pos-size_neighbor:pos+size_neighbor]
        print comment              
        print sequence
        
         
        
    
    positions = [0]*nb_insertions
    for i in range(nb_insertions): positions[i]=randint(0,limit)
    positions = sorted(positions, cmp=reverse_numeric) # In order to insert from right to left so the insertion positions are correct w.r.t the original genome. 
    seq_record.id+=" with insertions positions "+str(positions)
    for insertion_id in range(nb_insertions):
        pos = positions[insertion_id]
        insertion_size = randint(min_size_insertions,max_size_insertions)
        insertion = random_dna_sequence(insertion_size)
        comment=">DEL_"+str(insertion_id)+"|upper|"+str(pos)+"|"+str(insertion_size)+"|"+str(insertion)
        sequence=seq_record.seq[pos-size_neighbor:pos+size_neighbor]
        print comment              
        print sequence
        comment=">DEL_"+str(insertion_id)+"|lower|"+str(pos)+"|"+str(insertion_size)+"|"+str(insertion)
        seq_record.seq=seq_record.seq[0:pos]+insertion+seq_record.seq[pos:]
        sequence=seq_record.seq[pos-size_neighbor:pos+size_neighbor+insertion_size]
        print comment
        print sequence
        
        
        
        
    output_handle = open(my_output, "w")
    SeqIO.write(seq_record, output_handle, "fasta")
    output_handle.close()
    sys.exit(0)