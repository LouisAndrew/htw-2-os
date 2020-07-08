package ueb5;

public class BarrierAction implements Runnable {
        // private Worker worker;

        @Override
        public void run() {
                System.out.printf("BarrierAction: A^%d.v = (", Worker.potenz);
                for (int i = 0; i < U.MATRIX_DIM; i++) {
                        int temp = Worker.potenz == 2 ? Worker.AAv[i] : Worker.Av[i];
                        System.out.printf(" %d ", temp);
                }
                System.out.printf(")\n");
        }
}
