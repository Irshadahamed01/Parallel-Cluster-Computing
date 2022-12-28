#include <mpi.h>
#include <stdio.h>

int main() {
    int np;
    int pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Status sta;

    int seq01[4][8];
    int seq02[4][8];
    if (pid == 0) {
        seq01[0][0] = 1;
        seq01[0][1] = 1;
        seq01[0][2] = 0;
        seq01[0][3] = 0;
        seq01[0][4] = 0;
        seq01[0][5] = 0;
        seq01[0][6] = 1;
        seq01[0][7] = 1;

        seq01[1][0] = 1;
        seq01[1][1] = 0;
        seq01[1][2] = 1;
        seq01[1][3] = 1;
        seq01[1][4] = 0;
        seq01[1][5] = 1;
        seq01[1][6] = 1;
        seq01[1][7] = 0;

        seq01[2][0] = 0;
        seq01[2][1] = 0;
        seq01[2][2] = 0;
        seq01[2][3] = 0;
        seq01[2][4] = 0;
        seq01[2][5] = 1;
        seq01[2][6] = 1;
        seq01[2][7] = 0;

        seq01[3][0] = 1;
        seq01[3][1] = 1;
        seq01[3][2] = 1;
        seq01[3][3] = 1;
        seq01[3][4] = 0;
        seq01[3][5] = 1;
        seq01[3][6] = 0;
        seq01[3][7] = 1;

        seq02[0][0] = 1;
        seq02[0][1] = 0;
        seq02[0][2] = 0;
        seq02[0][3] = 0;
        seq02[0][4] = 1;
        seq02[0][5] = 0;
        seq02[0][6] = 0;
        seq02[0][7] = 1;

        seq02[1][0] = 1;
        seq02[1][1] = 1;
        seq02[1][2] = 0;
        seq02[1][3] = 1;
        seq02[1][4] = 1;
        seq02[1][5] = 1;
        seq02[1][6] = 0;
        seq02[1][7] = 0;

        seq02[2][0] = 0;
        seq02[2][1] = 1;
        seq02[2][2] = 0;
        seq02[2][3] = 0;
        seq02[2][4] = 0;
        seq02[2][5] = 1;
        seq02[2][6] = 1;
        seq02[2][7] = 0;

        seq02[3][0] = 1;
        seq02[3][1] = 1;
        seq02[3][2] = 0;
        seq02[3][3] = 1;
        seq02[3][4] = 1;
        seq02[3][5] = 1;
        seq02[3][6] = 0;
        seq02[3][7] = 1;
    }
    int rec_seq01[8];
    int rec_seq02[8];
    int ham_dis = 0;
    MPI_Scatter(&seq01, 8, MPI_INT, &rec_seq01, 8, MPI_INT,0, MPI_COMM_WORLD);
    MPI_Scatter(&seq02, 8, MPI_INT, &rec_seq02, 8, MPI_INT,0, MPI_COMM_WORLD);

    printf("\nMy Processor id is %d", pid);
    printf("\nReceived Data from sequence 1 is: ");
    for (int i = 0;i < 7;i++) {
        printf("%d ", rec_seq01[i]);
    }
    printf("\nReceived Data from sequence 2 is: ");
    for (int i = 0;i < 7;i++) {
        printf("%d ", rec_seq02[i]);
    }
    printf("\nHamming Distance: ");
    for (int i = 0;i < 7;i++) {
        if (rec_seq01[i] != rec_seq02[i]) {
            ham_dis++;
        }
    }
    printf("%d", ham_dis);
   
    int ham[8];
    int total = 0;
    MPI_Gather(&ham_dis, 1, MPI_INT, &ham, 1, MPI_INT,0, MPI_COMM_WORLD);

    if (pid == 0) {
        printf("\nHamming Distances are: ");
        for (int i = 0;i < 4;i++) {
            total = total + ham[i];
            printf("%d ", ham[i]);
        }
        printf("%d", total);
    }
    

    printf("\n#############################################");

    MPI_Finalize();
    return 0;

}

/*


C:\Users > mpiexec - n 4 Project1.exe

My Processor id is 1
Received Data from sequence 1 is: 1 0 1 1 0 1 1
Received Data from sequence 2 is : 1 1 0 1 1 1 0
Hamming Distance : 4
#############################################
My Processor id is 2
Received Data from sequence 1 is : 0 0 0 0 0 1 1
Received Data from sequence 2 is : 0 1 0 0 0 1 1
Hamming Distance : 1
#############################################
My Processor id is 3
Received Data from sequence 1 is : 1 1 1 1 0 1 0
Received Data from sequence 2 is : 1 1 0 1 1 1 0
Hamming Distance : 2
#############################################
My Processor id is 0
Received Data from sequence 1 is : 1 1 0 0 0 0 1
Received Data from sequence 2 is : 1 0 0 0 1 0 0
Hamming Distance : 3
Hamming Distances are : 3 4 1 2 10
#############################################


*/
