#!/bin/bash
#SBATCH --job-name=kmeans_OMP      
#SBATCH --output=kmeans_OMP.out   
#SBATCH --error=kmeans_OMP.err             
#SBATCH --ntasks=1                    
#SBATCH --cpus-per-task=20

module load opencv

export OMP_NUM_THREADS=20

k=$1
i=$2

if [z "$k" ] || [z "$i" ]; then
    echo "Usage: sbatch slurm.sh <k> <i>"
    exit 1
fi

# Execute the compiled program with command-line arguments
./exec/kmeans_OMP -k $k -i $i
