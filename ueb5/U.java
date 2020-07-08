package ueb5;

import java.util.Random;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class U {

        public static final int MATRIX_DIM = 4;

        public static void main(String[] args) {

                Thread thread;
                Lock lock = new ReentrantLock();
                BarrierAction action = new BarrierAction();
                CyclicBarrier barrier = new CyclicBarrier(MATRIX_DIM, action);
                
                Worker.A = createMatrixA(MATRIX_DIM);
                Worker.v = createMatrixV(MATRIX_DIM);

                System.out.printf("A Matrix: \n");
                for (int i = 0; i < Worker.A.length; i++) {
                        for (int j = 0; j < Worker.A[i].length; j++) {
                                System.out.printf(" %d ", Worker.A[i][j]);
                        }
                        System.out.printf("\n");
                }

                System.out.printf("v Matrix: \n");
                for (int i = 0; i < Worker.v.length; i++) {
                        System.out.printf(" %d ", Worker.v[i]);
                }

                for (int i = 0; i < MATRIX_DIM; i++ ) {
                        thread = new Thread(new Worker(i, lock, barrier));
                        thread.start();
                }
        }

        static int[][] createMatrixA(int matrixDim) {

                int[][] matrix = new int[matrixDim][matrixDim];
                for (int i = 0; i < matrixDim; i++) {
                        for (int j = 0; j < matrixDim; j++) {
                                matrix[i][j] = 0;
                        }
                        matrix[i][i == matrixDim - 1 ? 0 : i + 1] = 1;
                }

                return matrix;
        }

        static int[] createMatrixV(int matrixDim) {

                int[] matrix = new int[matrixDim];
                for (int i = 0; i < matrixDim; i++) {
                        matrix[getRandomBetween(0, matrixDim - 1)] = i + 1;
                }

                return matrix;
        }

        static int getRandomBetween(int min, int max) {
                return new Random().nextInt(max - min + 1) + min;
        }
}