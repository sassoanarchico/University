import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) {
		MatriceSparsa mat1 = readMatFF("mat.dat");
		System.out.println("Original Matrix:");
		System.out.println(mat1);
		System.out.println("################################################################################");
		System.out.println("TEST MAT_SET");
		System.out.println("################################################################################\n");
		System.out.println("");
		System.out.println("");
		System.out.println("Added -> 0,0,5");
		mat1.set(0, 0, 5);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 1,1,70");
		mat1.set(1, 1, 70);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 6,7,45");
		mat1.set(6, 7, 45);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 9,9,45");
		mat1.set(9, 9, 45);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 9,9,50");
		mat1.set(9, 9, 50);
		System.out.println(mat1);
		System.out.println("");
		System.out.println("Added -> 10,10,45");
		mat1.set(10, 10, 45);
		System.out.println(mat1);
		System.out.println("");

		System.out.println("################################################################################");
		System.out.println("TEST MAT_REMOVE");
		System.out.println("################################################################################\n");
		System.out.println("Removed -> 0,0,5\n");
		mat1.set(0, 0, 0);
		System.out.println(mat1);
		System.out.println("\n");
		System.out.println("Removed -> 1,1,70\n");
		mat1.set(1, 1, 0);
		System.out.println(mat1);
		System.out.println("\n");
		System.out.println("Removed -> 6,7,45\n");
		mat1.set(6, 7, 0);
		System.out.println(mat1);
		System.out.println("\n");
		System.out.println("Removed -> 5,5,45\n");
		mat1.set(5, 5, 0);
		System.out.println(mat1);
		System.out.println("\n");
		System.out.println("Removed -> 10,10,50\n");
		mat1.set(10, 10, 0);
		System.out.println(mat1);
		System.out.println("\n");

		System.out.println("################################################################################");
		System.out.println("TEST SOMMA");
		System.out.println("################################################################################\n");
		System.out.println("Matrix 1:");
		System.out.println(mat1);
		System.out.println("");
		MatriceSparsa mat2 = readMatFF("mat1.dat");
		System.out.println("Matrix 2:");
		System.out.println(mat2);
		System.out.println("");
		MatriceSparsa mat3 = MatriceSparsa.add(mat1, mat2);
		System.out.println("Matrix 1 + Matrix 2:");
		System.out.println(mat3);
		System.out.println("");

		System.out.println("################################################################################");
		System.out.println("TEST TRASPOSTA");
		System.out.println("################################################################################\n");
		MatriceSparsa mat4 = MatriceSparsa.tra(mat1);
		System.out.println("(Matrix 1)^T:");
		System.out.println(mat4);
		System.out.println("");

		System.out.println("################################################################################");
		System.out.println("TEST MOLTIPLICAZIONE");
		System.out.println("################################################################################\n");
		System.out.println("Matrix 1 + (Matrix 1)^T:");
		MatriceSparsa mat5 = MatriceSparsa.mul(mat1, mat4);
		System.out.println(mat5);
		System.out.println("");
		System.out.println("Finito");
	}

	private static MatriceSparsa readMatFF(String filename) {
		FileReader fr;
		try {
			fr = new FileReader(filename);
			BufferedReader br = new BufferedReader(fr);
			int m,n;
			String line = br.readLine();
			StringTokenizer st = new StringTokenizer(line);
			m = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			MatriceSparsa mat = new MatriceSparsa(m,n);
			for(int i = 0; i < m; i++) {
				line = br.readLine();
				st = new StringTokenizer(line);
				for(int j = 0; j < n; j++) {
					int x = Integer.parseInt(st.nextToken());
					mat.set(i, j, x);
				}
			}
			br.close();
			return mat;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}

}
