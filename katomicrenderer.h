/*******************************************************************
 *
 * Copyright 2006 Dmitry Suzdalev <dimsuz@gmail.com>
 *
 * This file is part of the KDE project "KAtomic"
 *
 * KAtomic is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * KAtomic is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KAtomic; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 ********************************************************************/
#ifndef KATOMIC_RENDERER_H
#define KATOMIC_RENDERER_H

#include <QHash>
#include <QSize>

class atom;
class KSvgRenderer;
class QPixmap;

/**
 *  Class for rendering elements of game SVG to QPixmap
 */
class KAtomicRenderer
{
public:
    /**
     *  Constructor.
     *  @param pathToSvg path to svg containing atom, bonds etc pictures
     */
    explicit KAtomicRenderer( const QString& pathToSvg );
    /**
     *  Destructor
     */
    ~KAtomicRenderer();
    /**
     *  Sets rendered element size and invalidates element cache.
     *  I.e. render* functions will return QPixmap of (size,size) dimentions
     */
    void setElementSize(int size);
    /**
     *  Sets Background size and invalidates background cache
     */
    void setBackgroundSize( const QSize& );
    /**
     *  Renders atom to pixmap.
     *  If setElementSize() wasn't called it assumes size of 30 px
     *  Atom pixmaps are cached (setElementsSize() invalidates the cache)
     */
    QPixmap renderAtom( const atom& );
    /**
     *  Renders non-atom elements (wall and arrows) to pixmap.
     *  @param element if == '#' will render a wall, if '<','>','^','_' will render
     *  arrow-left,arrow-right,arrow-up or arrow-down
     *  Elements pixmaps are cached (setElementsSize() invalidates the cache)
     */
    QPixmap renderNonAtom( char element );
    /**
     *  Renders backgound to QPixmap of size set by setBackgroundSize
     *  Background pixmap is cached (setBackgroundSize() invalidates the cache)
     */
    QPixmap renderBackground();
private:
    /**
     * Creates hashes for translating atom and bond signatures found in
     * level files to corresponding SVG-element names
     */
    void fillNameHashes();
    /**
     *  Renders this atom pixmaps and puts them in cache in case they arent there yet
     */
    void ensureAtomIsInCache(const atom&);

    KSvgRenderer *m_renderer;
    QHash<char, QString> m_names; // cryptic_char -> elemName
    QHash<char, QString> m_bondNames; // cryptic_char -> bondName

    int m_elemSize;
    QSize m_bkgndSize;
};

#endif
