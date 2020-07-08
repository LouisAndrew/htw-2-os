package ueb5;

import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.Lock;

public class Worker implements Runnable {

        public static int[][] A;
        public static int[] v;
        public static int[] Av = new int[U.MATRIX_DIM];
        public static int[] AAv = new int[U.MATRIX_DIM];
        public static int potenz;

        private int rowNum;
        private Lock lock;
        private CyclicBarrier barrier;

        public Worker(int rowNum, Lock lock, CyclicBarrier barrier) {
                this.rowNum = rowNum;
                this.lock = lock;
                this.barrier = barrier;
        }

        @Override
        public void run() {

                int[] row = A[rowNum];
                try {
                        // first -> calculate 1. potenz and assign to Av
                        potenz = 1;
                        Av[rowNum] = calculate(row, v);
                        print(Av);
                        barrier.await();

                        // then -> calculate 2. potenz and assign to AAv
                        potenz = 2;
                        AAv[rowNum] = calculate(row, Av);
                        print(AAv);
                        barrier.await();
                } catch (InterruptedException ex) {
                } catch (BrokenBarrierException ex) {
                }
        }

        private int calculate(int[] v1, int[] v2) {

                if (v1.length != v2.length) {
                        return Integer.MIN_VALUE;
                }

                int result = 0;
                for (int i = 0; i < v1.length; i++) {
                        result += v1[i] * v2[i];
                }

                try {
                        // give small sleep.
                        Thread.sleep(new Random().nextInt(10) * 100);
                } catch (InterruptedException ex) {
                        ex.printStackTrace();
                }

                return result;
        }

        private void print(int[] v) {

                // enter critical region.
                lock.lock();
                System.out.printf("Worker %d, A^%d.v: (", rowNum + 1, potenz);
                for (int i = 0; i < v.length; i++) {
                        System.out.printf(" %d ", v[i]);
                }
                System.out.printf(")\n");
                lock.unlock();
        }

}