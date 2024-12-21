/*
    @author: Barkın_Saday
    @project_name: Lab04
    @date: 25.11.2020
 */
public class PotLuckGame {
    public static void main(String[] args)
    {
        int row = 8;
        int column = 4;
        PotLuck game = new PotLuck(row, column);
        game.setVisible(true);
    }
}
