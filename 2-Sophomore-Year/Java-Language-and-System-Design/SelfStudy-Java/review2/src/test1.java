interface Open {
    int x = 0;
}

class Father {
    int x = 1;
}

class Son extends Father implements Open {
    public void px() {
        System.out.println(x);
    }
    public static void main(String[] args) {
        new Son().px();
    }
}
