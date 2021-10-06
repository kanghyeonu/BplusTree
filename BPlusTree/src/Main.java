public class Main {

	public static void main(String[] args) {
		BPTree BPT = new BPTree();
		
		BPT.insert("r");
		BPT.insert("a");
		BPT.insert("d");
		BPT.insert("b");
		BPT.insert("h");
		BPT.insert("q");

		BPT.PreOrder();
	}

}
