package com.game.src.main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;

public class Menu {
	
	public Rectangle playbut = new Rectangle(Game.WIDTH/2 +120,150,100,50);
	public Rectangle helpbut = new Rectangle(Game.WIDTH/2 +120,250,100,50);
	public Rectangle quitbut = new Rectangle(Game.WIDTH/2 +120,350,100,50);
	
	public void render(Graphics g){
		Graphics2D g2d = (Graphics2D) g;
		
		Font fnt0 = new Font("arial", Font.BOLD, 50);
		g.setFont(fnt0);
		g.setColor(Color.white);
		g.drawString("SE-800", Game.WIDTH/2, 100);
		
		Font fnt1 = new Font("arial", Font.BOLD, 30);
		g.setFont(fnt1);
		g.drawString("Play",playbut.x + 19,playbut.y + 30);
		g.drawString("Help",helpbut.x + 19,helpbut.y + 30);
		g.drawString("Quit",quitbut.x + 19,quitbut.y + 30);
		g2d.draw(playbut);
		g2d.draw(helpbut);
		g2d.draw(quitbut);
	}
}
