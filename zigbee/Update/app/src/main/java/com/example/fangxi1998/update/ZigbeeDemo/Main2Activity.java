package com.example.fangxi1998.update.ZigbeeDemo;

import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v4.view.ViewPager;
import android.support.design.widget.BottomNavigationView;
import android.view.MenuItem;

import com.example.fangxi1998.update.R;
import com.example.fangxi1998.update.ZigbeeDemo.FragmentAdapter;

public class Main2Activity extends AppCompatActivity {

    private ViewPager vp;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        FragmentAdapter fragmentAdapter=new FragmentAdapter(getSupportFragmentManager());
        vp=findViewById(R.id.viewpager);
        vp.setAdapter(fragmentAdapter);
        final BottomNavigationView bottom = findViewById(R.id.bottom);
        bottom.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                switch (item.getItemId()) {
                    case R.id.one:
                        vp.setCurrentItem(0);
                        break;
                    case R.id.two:
                        vp.setCurrentItem(1);
                        break;
                    case R.id.three:
                        vp.setCurrentItem(2);
                        break;
                }
                return true;
            }
        });

        vp.addOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override
            public void onPageSelected(int position) {
                bottom.getMenu().getItem(position).setChecked(true);
            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });
    }
}
