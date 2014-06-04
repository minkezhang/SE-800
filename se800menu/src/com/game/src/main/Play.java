package com.game.src.main;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.io.File;
import java.io.IOException;

public class Play {
	
	public Rectangle playbut = new Rectangle(Game.WIDTH/2 +120,150,105,50);
	public Rectangle helpbut = new Rectangle(Game.WIDTH/2 +120,250,105,50);
	public Rectangle quitbut = new Rectangle(Game.WIDTH/2 +120,350,105,50);
	public Rectangle select = new Rectangle(Game.WIDTH/2 +120,050,105,50);
	
	public void render(Graphics g, int key){
		Graphics2D g2d = (Graphics2D) g;
		
		
		Font fnt0 = null;//new Font("arial", Font.BOLD, 50);
		try {
			fnt0 = Font.createFont(Font.TRUETYPE_FONT, new File("me123.TTF"));
			fnt0 = fnt0.deriveFont(Font.PLAIN,50);
			GraphicsEnvironment ge = 
					GraphicsEnvironment.getLocalGraphicsEnvironment();
			 ge.registerFont(fnt0);
			 } catch (IOException|FontFormatException e) {
				 
			 }
		g.setFont(fnt0);
		Color high = new Color(125, 250, 250, 195);
		g.setColor(high);
		select.y = (key*100) + 50;
		g2d.draw(select);
		g2d.fill(select);
		//g.setColor(Color.white);
		Color ttle = new Color(250, 125, 125, 105);
		g.setColor(ttle);
		g.drawString("SE-800", Game.WIDTH/2 +10, 100);
		
		Font fnt1 = new Font("arial", Font.BOLD, 30);
		g.setFont(fnt1);
		g.drawString("Play",playbut.x + 21,playbut.y + 30);
		g.drawString("Credits",helpbut.x + 2,helpbut.y + 30);
		g.drawString("Quit",quitbut.x + 21,quitbut.y + 30);
		g2d.draw(playbut);
		g2d.draw(helpbut);
		g2d.draw(quitbut);
	}
	
}
