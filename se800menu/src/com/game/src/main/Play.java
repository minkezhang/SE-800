package com.game.src.main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;

public class Play {
	//Credit Submenu
	//rectangle( x, y, width, height)
	public Rectangle back = new Rectangle(10,10,110,50);
	public Rectangle servme = new Rectangle(210,70,75,40);
	public Rectangle clieme = new Rectangle(310,70,75,40);
	public Rectangle porten = new Rectangle(210,140,80,40);
	public Rectangle addrn1 = new Rectangle(210,210,80,40);
	public Rectangle addrn2 = new Rectangle(310,210,80,40);
	public Rectangle addrn3 = new Rectangle(410,210,80,40);
	public Rectangle addrn4 = new Rectangle(510,210,80,40);
	public Rectangle cred = new Rectangle(210,280,60,40);
	public Rectangle cblu = new Rectangle(290,280,60,40);
	public Rectangle cgre = new Rectangle(370,280,60,40);
	public Rectangle cyel = new Rectangle(450,280,60,40);
	public Rectangle corg = new Rectangle(530,280,60,40);
	public Rectangle bgmb = new Rectangle(600,20,20,20);
	public Rectangle selbgmb = new Rectangle(600,20,20,20);
	//color
	public Color top = new Color(250, 125, 125, 105);
	public Color high = new Color(125, 250, 250, 195);
	public Color color2 = new Color(250, 250, 150, 195);
	public Color color3 = new Color(225, 250, 150, 195);
	public Color color4 = new Color(225, 250, 150, 195);
	public Color myred = new Color(255, 50, 50, 255);
	public Color supred = new Color(255, 0, 0, 195);
	public Color myblu = new Color(50, 50, 255, 255);
	public Color supblu = new Color(0, 0, 255, 195);
	public Color mygre = new Color(10, 255, 50, 255);
	public Color supgre = new Color(0, 255, 0, 195);
	public Color myyel = new Color(255, 255, 50, 255);
	public Color supyel = new Color(255, 255, 0, 195);
	public Color myorg = new Color(255, 128, 50, 255);
	public Color suporg = new Color(255, 128, 0, 195);
	//font
	public Font fntt = new Font("arial", Font.BOLD, 30);
	public Font fnt0 = new Font("arial", Font.PLAIN, 15);
	public Font fnt1 = new Font("arial", Font.BOLD, 30);
	// RED, BLUE, GREEN, YELLOW, ORANGE
	
	//public Rectangle body = new Rectangle(10,100,Game.WIDTH/2 + 360,Game.HEIGHT/2+230);
	public Rectangle select = new Rectangle(10,10,110,50);
	public Rectangle submit = new Rectangle(210,350,110,50);
	public Rectangle thghli = new Rectangle(215,140,18,40);
	
	Game game;
	
	public Play(Game game){
		this.game = game;
	}
	
	public void render(Graphics g, int key){
		Graphics2D g2d = (Graphics2D) g;
		
		if(this.game.bgmon == true){
		g.setColor(top);
		g2d.draw(selbgmb);
		g2d.fill(selbgmb);
		}
		g.setColor(high);
		switch(key){
		case 1:
			select.x = 10;
			select.y = 10;
			select.width = 110;
			select.height = 50;
			break;
		case 2:
			select.x = 210;
			select.y = 70;
			select.width = 75;
			select.height = 40;
			break;
		case 3:
			select.x = 310;
			select.y = 70;
			select.width = 75;
			select.height = 40;
			break;
		case 4:
			select.x = 210;
			select.y = 140;
			select.width = 80;
			select.height = 40;
			break;
		case 5:
			select.x = 210;
			select.y = 210;
			select.width = 80;
			select.height = 40;
			break;
		case 6:
			select.x = 310;
			select.y = 210;
			select.width = 80;
			select.height = 40;
			break;
		case 7:
			select.x = 410;
			select.y = 210;
			select.width = 80;
			select.height = 40;
			break;
		case 8:
			select.x = 510;
			select.y = 210;
			select.width = 80;
			select.height = 40;
			break;
		case 9:
			select.x = 208;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 10:
			select.x = 288;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 11:
			select.x = 368;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 12:
			select.x = 448;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 13:
			select.x = 528;
			select.y = 278;
			select.width = 64;
			select.height = 44;
			break;
		case 14:
			select.x = 210;
			select.y = 350;
			select.width = 110;
			select.height = 50;
			break;
		}
		g2d.draw(select);
		g2d.fill(select);
		//////////
		g.setColor(color2);
		switch(key){
		case 4://port
			thghli.x = 215;
			thghli.y = 140;
			thghli.x = 215 + this.game.tiscounter*18;
			break;
		case 5://addr1
			thghli.x = 215;
			thghli.y = 210;
			thghli.x = 215 + this.game.tiscounter*18;
			break;
		case 6://addr2
			thghli.x = 315;
			thghli.y = 210;
			thghli.x = 315 + this.game.tiscounter*18;
			break;
		case 7://addr3
			thghli.x = 415;
			thghli.y = 210;
			thghli.x = 415 + this.game.tiscounter*18;
			break;
		case 8://addr4
			thghli.x = 515;
			thghli.y = 210;
			thghli.x = 515 + this.game.tiscounter*18;
			break;
		default:
			thghli.x = 215;
			thghli.y = 140;
			break;
		}
		g2d.fill(thghli);
		g.setColor(top);
		g.setFont(fntt);
		//port number
		g.drawString(Integer.toString(this.game.portnum[0]),porten.x+6,porten.y+32);
		g.drawString(Integer.toString(this.game.portnum[1]),porten.x+24,porten.y+32);
		g.drawString(Integer.toString(this.game.portnum[2]),porten.x+42,porten.y+32);
		g.drawString(Integer.toString(this.game.portnum[3]),porten.x+60,porten.y+32);
		//address 1
		g.drawString(Integer.toString(this.game.addr1[0]),addrn1.x+6,addrn1.y+32);
		g.drawString(Integer.toString(this.game.addr1[1]),addrn1.x+24,addrn1.y+32);
		g.drawString(Integer.toString(this.game.addr1[2]),addrn1.x+42,addrn1.y+32);
		//g.drawString("0",addrn1.x+60,addrn1.y+32);
		//address 2
		g.drawString(Integer.toString(this.game.addr2[0]),addrn2.x+6,addrn2.y+32);
		g.drawString(Integer.toString(this.game.addr2[1]),addrn2.x+24,addrn2.y+32);
		g.drawString(Integer.toString(this.game.addr2[2]),addrn2.x+42,addrn2.y+32);
		//g.drawString("0",addrn2.x+60,addrn2.y+32);
		//address 3
		g.drawString(Integer.toString(this.game.addr3[0]),addrn3.x+6,addrn3.y+32);
		g.drawString(Integer.toString(this.game.addr3[1]),addrn3.x+24,addrn3.y+32);
		g.drawString(Integer.toString(this.game.addr3[2]),addrn3.x+42,addrn3.y+32);
		//g.drawString("0",addrn3.x+60,addrn3.y+32);
		//address 4
		g.drawString(Integer.toString(this.game.addr4[0]),addrn4.x+6,addrn4.y+32);
		g.drawString(Integer.toString(this.game.addr4[1]),addrn4.x+24,addrn4.y+32);
		g.drawString(Integer.toString(this.game.addr4[2]),addrn4.x+42,addrn4.y+32);
		//g.drawString("0",addrn4.x+60,addrn4.y+32);
		//////////
		g.setColor(top);
		g.setFont(fnt0);
		g.drawString("BGM",bgmb.x-38,bgmb.y+16);
		g2d.draw(bgmb);
		g.setFont(fnt1);
		g.drawString("<<Back",back.x+1,back.y+36);
		g.drawString("Host Type",servme.x-200,servme.y+30);
		g.drawString("Port",porten.x-200,porten.y+30);
		g.drawString("Address",addrn1.x-200,addrn1.y+30);
		g.drawString("Ship Color",cred.x-200,cred.y+30);
		g.drawString("Submit",submit.x+4,submit.y+36);
		g2d.draw(back);
		if(this.game.host == true){
			g.setColor(color3);
			g2d.fill(servme);
		}
		g.setColor(top);
		g2d.draw(servme);
		if(this.game.host == false){
			g.setColor(color4);
			g2d.fill(clieme);
		}
		g.setColor(top);
		g2d.draw(clieme);
		g.drawString("Serv",servme.x+4,servme.y+30);
		g.drawString("Peer",clieme.x+4,servme.y+30);
		g2d.draw(porten);
		g2d.draw(addrn1);
		g2d.draw(addrn2);
		g2d.draw(addrn3);
		g2d.draw(addrn4);
		if(this.game.color == "RED")
			g.setColor(myred);
		else
		g.setColor(supred);
		g2d.draw(cred);
		g2d.fill(cred);
		if(this.game.color == "BLUE")
			g.setColor(myblu);
		else
		g.setColor(supblu);
		g2d.draw(cblu);
		g2d.fill(cblu);
		if(this.game.color == "GREEN")
			g.setColor(mygre);
		else
		g.setColor(supgre);
		g2d.draw(cgre);
		g2d.fill(cgre);
		if(this.game.color == "YELLOW")
			g.setColor(myyel);
		else
		g.setColor(supyel);
		g2d.draw(cyel);
		g2d.fill(cyel);
		if(this.game.color == "ORANGE")
			g.setColor(myorg);
		else
		g.setColor(suporg);
		g2d.draw(corg);
		g2d.fill(corg);
		g.setColor(top);
		g2d.draw(submit);
	}
	
}
