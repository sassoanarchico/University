class Node<V> {
	public int key; // Chiave
	public V value; // Valore
	public Node<V> left; // Riferimento al figlio sinistro
	public Node<V> right; // Riferimento al figlio destro

	public Node(int key, V value) {
		this.key = key;
		this.value = value;
	}
}
