import java.util.*;

public class BST<V> {

    private Node<V> root;
    private int size; // Numero di nodi del BST


    public BST(int key, V value) {
        this.root = new Node<V>(key, value);
        this.size = 1;
    }

	// Restituisce un riferimento alla radice del BST
	public Node<V> root() {
		return this.root;
	}
	
	// Restituisce il numero di nodi presenti nel BST
	public int size() {	
		return this.size;
	}
	
	// Metodo ausiliario per l'inserimento di una coppia (chiave, valore) nel BST
    private void insert(Node<V> t, int k, V v) {

        if (t.key == k) {

            t.value = v;

        } else if (k < t.key) {

            if (t.left == null) {
                t.left = new Node<V>(k, v);
                this.size++;
            }
            else
                insert(t.left, k, v);

        } else {

            if (t.right == null) {
                t.right = new Node<V>(k, v);
                this.size++;
            }
            else
                insert(t.right, k, v);

        }
    }

	// Metodo che inserisce una coppia (chiave, valore) nel BST
    public void insert(int k, V v) {

        if (this.root == null)
            this.root = new Node<V>(k, v);

        else
            insert(this.root, k, v);
    }
    
    
	// Metodo ausiliario di public V find(int k)
    private V find(Node<V> t, int k) {

        if (t == null)
            return null;

        else if (t.key == k)
            return t.value;

        else if (k < t.key)
            return find(t.left, k);

        else
            return find(t.right, k);
    }

	// Restituisce il valore associato alla chiave k, se esistente
    public V find(int k) {
        if (this.root == null)
            return null;
        else
            return find(this.root, k);
    }

	// Metodo ausiliario di findMin()
    private Node<V> findMin(Node<V> t) {

        if (t.left == null)
            return t;

        return findMin(t.left);
    }

	// Restituisce il valore della chiave minima
    public int findMin() {

        if (this.root == null)
            return -1;

        return findMin(this.root).key;
    }


	// Metodo ausiliario di removeMin()
    private Node<V> removeMin(Node<V> t) {

        // we are on the min key
        if (t.left == null) {
            return t.right;
        }

        t.left = removeMin(t.left);
        return t;
    }

	// Rimuove il nodo associato alla chiave di valore minimo
    public void removeMin() {

        if (this.root == null)
            return;

        this.root = removeMin(this.root);
    }

	// Metodo ausiliario di remove(int k)
    private Node<V> remove(Node<V> n, int k) {

        if (n == null) return null;

        else if (k < n.key)
            n.left = remove(n.left, k);

        else if (k > n.key)
            n.right = remove(n.right, k);

        else {

            if (n.right == null) {
                this.size--;
                return n.left;
            }

            if (n.left == null) {
                this.size--;
                return n.right;
            }

            // two children case
            Node<V> to_remove = n;

            n = findMin(to_remove.right);
            Node<V> nn = new Node<V>(n.key, n.value);
            nn.right = removeMin(to_remove.right);
            nn.left = to_remove.left;
            n = nn;
            this.size--;
        }

        return n;
    }


	// Rimuove il nodo associato alla chiave k, se esistente
    public void remove(int k) {

        if (this.root == null)
            return;

        this.root = remove(this.root, k);
    }

	// Metodo ausiliario di print()
    private void print(Node<V> t, int level) {

        if (t == null)
            return;

        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" |--");
        }

        System.out.println(t.key);

        print(t.left, level + 1);
        print(t.right, level + 1);
    }

	// Stampa una rappresentazione del BST su stdout
    public void print(){
        print(this.root, 0);
    }

}
