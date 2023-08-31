public class MatriceSparsa {

	private class Elem{
		int i;
		int j;
		int x;
		Elem next;
	}

	private int m;
	private int n;
	Elem head;

	public MatriceSparsa(int m, int n) {
		super();
		this.m = m;
		this.n = n;
	}

	public int getNumRow() {
		return m;
	}

	public int getNumCol() {
		return n;
	}

	public void mat_remove(int i, int j){
		Elem it = this.head;
		Elem aux = it;

		while(it != null){
			if (it.i == i && it.j == j) {
				if(it.equals(this.head)){
					this.head = it.next;
					return;
				}
				aux.next = it.next;	
				return;
			}
			aux = it;
			it = it.next;
		}
	}

	public void set(int i, int j, int x) {
		if(i >= this.m || j >= this.n){
			System.out.println("Gli indici inseriti superano i limiti della matrice!");
			return;
		}

		if (x == 0) {
			this.mat_remove(i,j);
			return;
		}
		Elem toPut = new Elem();
		toPut.x = x;
		toPut.i = i;
		toPut.j = j;
		toPut.next = null;

		Elem it = this.head;

		if(it == null || it.i > i || (it.i == i && it.j > j)) {
			toPut.next = this.head;
			this.head = toPut;
			return;
		}
		if(it.i == i && it.j == j) {
			it.x = x;
			return;
		}
		while(it.next != null) {
			if(it.i == i && it.j == j) {
				it.x = x;
				return;
			}
			if(it.next.i > i || (it.next.i ==i && it.next.j > j)) {
				toPut.next = it.next;
				it.next = toPut;
				return;
			}
			it = it.next;
		}
		if(it.i == i && it.j == j) {
			it.x = x;
			return;
		}
		it.next = toPut;
	}

	public int get(int i, int j) {
		Elem it = this.head;
		while(it != null) {
			if(it.i == i && it.j == j) {
				return it.x;
			}
			it = it.next;
		}
		return 0;
	}

	public String toString() {
		StringBuffer ret = new StringBuffer("");
		int i,j;
		Elem it = this.head;
		for(i = 0; i< this.m; i++) {
			for (j= 0; j<this.n; j++) {
				if (it == null || (it.i > i && it.j > j)) {
					ret.append("0 ");
				}
				else if (it.i == i && it.j == j) {
					ret.append(it.x + " ");
					it = it.next;
				}
				else {
					ret.append("0 ");
				}
			}
			ret.append("\n");
		}
		return ret.toString();
	}

	public static MatriceSparsa add(MatriceSparsa mat1, MatriceSparsa mat2) {
		int row1, row2, col1, col2;
		row1 = mat1.getNumRow();
		row2 = mat2.getNumRow();
		col1 = mat1.getNumCol();
		col2 = mat2.getNumCol();
		if(row1 != row2 || col1 != col2) {
			throw new RuntimeException("Impossibile sommare le due matrici, dimensioni differenti");
		}
		MatriceSparsa ret = new MatriceSparsa(row1, col1);
		Elem it1 = mat1.head;
		Elem it2 = mat2.head;
		while(it1 != null || it2 != null){
			if (it1 != null && it2 != null) {
				if (it1.i < it2.i || (it1.i == it2.i && it1.j < it2.j)) {
					ret.set(it1.i, it1.j, it1.x);
					it1 = it1.next;
				}
				else if(it1.i == it2.i && it1.j == it2.j) {
					ret.set(it1.i, it1.j, (it1.x + it2.x));
					it1 = it1.next;
					it2 = it2.next;
				}
				else {
					ret.set(it2.i, it2.j, it2.x);
					it2 = it2.next;
				}
			}
			else if(it2 != null) {
				ret.set(it2.i, it2.j, it2.x);
				it2 = it2.next;
			}
			else if (it1 != null) {
				ret.set(it1.i, it1.j, it1.x);
				it1 = it1.next;
			}
		}
		return ret;
	}

	public static MatriceSparsa tra(MatriceSparsa mat) {
		MatriceSparsa ret = new MatriceSparsa(mat.getNumCol(), mat.getNumRow());
		Elem it = mat.head;
		while (it != null) {
			ret.set(it.j, it.i, it.x);
			it = it.next;
		}
		return ret;
	}

	public static MatriceSparsa mul(MatriceSparsa mat1, MatriceSparsa mat2) {
		int row1, row2, col1, col2;
		row1 = mat1.getNumRow();
		row2 = mat2.getNumRow();
		col1 = mat1.getNumCol();
		col2 = mat2.getNumCol();
		if(col1 != row2) {
			throw new RuntimeException("Impossibile sommare le due matrici, dimensioni differenti");
		}
		MatriceSparsa ret = new MatriceSparsa(row1, col2);
		int i,j,k,val;
		for (i = 0; i < row1; i++) {
			for(j = 0; j < col2; j++) {
				val = 0;
				for (k = 0; k < col1; k++) {
					val += (mat1.get(i, k) * mat2.get(k, j));
				}
				if (val != 0) {
					ret.set(i, j, val);
				}
			}
		}
		return ret;
	}
}
