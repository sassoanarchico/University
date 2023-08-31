import java.util.*;

public class BSTServices {

	public LinkedList ordina(BST t) {
		LinkedList<Integer> ret = new LinkedList<Integer>();
	
		while(t.size() >= 1){
			int min = t.findMin();
			ret.addFirst(min);
			t.remove(min);
		}
		return ret;
		
	}
		
	public LinkedList outer_range(BST t, int k1, int k2) {
		LinkedList<Integer> ret = new LinkedList<Integer>();
		while(t.size() >= 1) {
			int min =t.findMin();
			if (min < k1 || min > k2) {
				ret.add(min);
			}
			t.remove(min);
		}
		return ret;

	}
	
	public int altezza(BST t) {
		return altezzaHelper(t.root());
	}

	private int altezzaHelper(Node node) {
        if (node == null)
            return -1;

        int leftHeight = altezzaHelper(node.left);
        int rightHeight = altezzaHelper(node.right);

        return Math.max(leftHeight, rightHeight) + 1;
    }

	
}
