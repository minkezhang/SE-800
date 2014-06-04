package com.game.src.main;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import com.game.src.main.Game.STATE;

public class MouseInput implements MouseListener{
	
	Game game;
	
	public MouseInput(Game game){
		this.game = game;
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		int mx = e.getX();
		int my = e.getY();
		/**
		public Rectangle playbut = new Rectangle(Game.WIDTH/2 +120,150,100,50);
		public Rectangle helpbut = new Rectangle(Game.WIDTH/2 +120,250,100,50);
		public Rectangle quitbut = new Rectangle(Game.WIDTH/2 +120,350,100,50);
		public Rectangle back = new Rectangle(10,10,110,50);
		 */
		
		if(Game.State == STATE.MENU){
		if(mx >= Game.WIDTH / 2 + 120 && mx <= Game.WIDTH/2 + 220){
			if(my >= 150 && my <= 200){
				//pressed play
				//Game.State = Game.STATE.GAME;
				game.openGAME("8000","127.0.0.1","BLUE");
			}else if(my >= 250 && my <= 300){
				//credits
				Game.State = STATE.CREDITS;
			}else if(my >= 350 && my <= 400){
				//quit game
				System.exit(1);
			}
		}
		}else if(Game.State == STATE.PLAY){
			
			
		}else if(Game.State == STATE.CREDITS){
			if(mx >= 10 && mx <= 120 && my >= 10 && my <= 60)
				Game.State = STATE.MENU;
		}
	}


	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
