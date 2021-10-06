/*----------------------------------------* 
 * 
 * 6 way B+Tree
 * node 당 child 개수 = 3개 ~ 6개
 * node 당 Key 개수 = 2개 ~ 5개
 * 
 *----------------------------------------*/

public class BPTree {
	private Node root;
	private LeafNode head;
	private int Degree;
	private int min_child, min_Key, max_child, max_key;
	
	BPTree(){
		this.root = null;
		this.head = null;
		this.Degree = 6;
		setParam(this.Degree);
	}
	
	BPTree(int Degree){
		this.root = null;
		this.head = null;
		if(Degree%2 == 0)
			this.Degree = Degree;
		else
			this.Degree = Degree+1;		
		setParam(this.Degree);
	}
	
	private void setParam(int Degree){
		this.min_child = this.Degree/2;
		this.max_child = this.Degree;
		this.min_Key = this.Degree/2 - 1;
		this.max_key = this.Degree - 1;	
	}
	
	void insert(String data) {
		//트리가 비었을 때
		if(this.root == null) {
			LeafNode newnode = new LeafNode(this.Degree);
			this.root = newnode;
			this.head = newnode;
			newnode.insert(this ,data);
			return;
		}
		//트리가 존재하면
		this.root.insert(this ,data);
	}
	
	void setRoot(Node node) {
		this.root = node;
	}
	void PreOrder() {
		this.root.PreOrder();
	}
}
