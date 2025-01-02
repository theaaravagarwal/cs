public class hashTable {
    private static final int TABLE_SIZE = 1000;
    private static final int PRIME = 31;
    private static final int MOD = 1000000007;

    private int[] table;

    public hashTable() {
        table = new int[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    private int hash(int key) {
        return (int) ((long) key * PRIME % MOD);
    }

    public void insert(int key) {
        int index = hash(key);
        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index] = key;
    }

    public boolean contains(int key) {
        int index = hash(key);
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        return false;
    }

    public void remove(int key) {
        int index = hash(key);
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        }
    }
}