public class Tree {

    private int key;
    private Tree left;
    private Tree right;

    public Tree(int key) {
        this.key = key;
    }

    public static Tree build_1() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.left = n3;
        n6.right = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_2() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.right = n3;
        n6.left = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_3() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);

        n6.left = n3;

        n3.left = n1;
        n3.right = n5;

        n5.right = n12;

        return n6;
    }

    private int isBST(Tree v, int last_max) {

        if(v == null)
            return last_max;

        int max = isBST(v.left, last_max);
        if(max == -1 || max > v.key)
            return -1;

        return isBST(v.right, v.key);
    }

    public boolean isBST() {

        int res = isBST(this, 0); // tutte le chiavi sono interi positivi
        if (res < 0)
            return false;

        return true;
    }

    private int isBalanced(Tree v) {

        if(v == null)
            return 0;

        int l = isBalanced(v.left);
        int r = isBalanced(v.right);

        if(l < 0 || r < 0)
            return -1;

        int diff = l >= r ? l - r : r - l;
        if(diff <= 1)
            return (l >= r ? l : r) + 1;

        return -1;
    }

    public boolean isBalanced() {

        int res = isBalanced(this);
        if (res < 0)
            return false;

        return true;
    }

    private int isAVL(Tree v, int last_max, Height h) {

        if(v == null) {
            h.height = 0;
            return last_max;
        }

        Height hl = new Height();
        Height hr = new Height();

        int max = isAVL(v.left, last_max, hl);

        if(max == -1 || max > v.key)
            return -1;

        max = isAVL(v.right, v.key, hr);

        if(hl.height < 0 || hr.height < 0)
            return -1;

        int diff = hl.height >= hr.height ? hl.height - hr.height : hr.height - hl.height;
        if(diff <= 1) {
            h.height = (hl.height >= hr.height ? hl.height : hr.height) + 1;
        } else {
            return -1;
        }

        return max;
    }

    public boolean isAVL() {

        Height h = new Height();
        int res = isAVL(this, 0, h);
        if (res < 0 || h.height < 0)
            return false;

        return true;
    }

    private class Height {
        int height;
    }

}
