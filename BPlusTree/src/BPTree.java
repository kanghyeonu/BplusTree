/*----------------------------------------* 
 * 
 * 6 way B+Tree
 * node �� child ���� = 3�� ~ 6��
 * node �� Key ���� = 2�� ~ 5��
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
		this.min_child = this.Degree/2;
		this.max_child = this.Degree;
		this.min_Key = this.Degree/2 - 1;
		this.max_key = this.Degree - 1;	
	}
	
	BPTree(int Degree){
		this.root = null;
		this.head = null;
		if(Degree%2 == 0)
			this.Degree = Degree;
		else
			this.Degree = Degree+1;		
		this.min_child = this.Degree/2;
		this.max_child = this.Degree;
		this.min_Key = this.Degree/2 - 1;
		this.max_key = this.Degree - 1;
	}
	
	void insert(String data) {
		this.insert(data, this.Degree);
	}
	
	private void insert(String data, int Degree) {
		//��Ʈ�� ���������
		if(this.root == null)
		{
			LeafNode newnode = new LeafNode(Degree);
			this.root = newnode;
			this.head = newnode;
			this.root.insert(data, Degree);
			return;
		}
		//Ʈ���� ���� ��, ��Ʈ���� ��ȸ �� �˸��� leafnode�� ���� �� �� leaf��� ��ȯ
		Node temp = this.root.insert(data, this.max_key);;
		
		
		//case 1. ���� �� ������ �Ͼ�� �ʴ� ���
		
		//case 2. ������ �Ͼ�� ���
	}
}
