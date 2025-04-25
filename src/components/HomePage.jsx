// HomePage.jsx
import React, { useState, useEffect } from "react";
import "./HomePage.css";
import homeImage from "../assets/homeImage.jpeg";
import planta1 from "../assets/planta1.jpeg";
import planta2 from "../assets/planta2.jpeg";
import planta3 from "../assets/planta3.jpeg";
import plantDRY from "../assets/plantDRY.png";

function HomePage() {
  const [plant1Indicators, setPlant1Indicators] = useState({
    moisture:    { value: 75, display: "75%", min: 65, max: 85 },
    temperature: { value: 21, display: "21°C", min: 18, max: 24 },
    pH:          { value: 6.0, display: "6.0", min: 5.5, max: 6.5 },
  });

  const [plant2Indicators, setPlant2Indicators] = useState({
    moisture:    { value: 65, display: "65%", min: 55, max: 75 },
    temperature: { value: 18, display: "18°C", min: 15, max: 20 },
    pH:          { value: 6.5, display: "6.5", min: 6.0, max: 7.0 },
  });

  const [plant3Indicators, setPlant3Indicators] = useState({
    moisture:    { value: 25, display: "25%", min: 15, max: 35 },
    temperature: { value: 25, display: "25°C", min: 20, max: 30 },
    pH:          { value: 6.8, display: "6.8", min: 6.0, max: 7.5 },
  });

  // Gera mudança suave
  const generateSmoothChange = (currentValue, min, max, maxChange) => {
    const change = (Math.random() * 2 - 1) * maxChange;
    let newValue = currentValue + change;
    return Math.max(min, Math.min(max, newValue));
  };

  // Funções de atualização
  const updateMoisture = (current) => {
    const v = generateSmoothChange(current.value, current.min, current.max, 3);
    return { value: v, display: `${Math.round(v)}%`, min: current.min, max: current.max };
  };
  const updateTemperature = (current) => {
    const v = generateSmoothChange(current.value, current.min, current.max, 0.5);
    return { value: v, display: `${v.toFixed(1)}°C`, min: current.min, max: current.max };
  };
  const updatePH = (current) => {
    const v = generateSmoothChange(current.value, current.min, current.max, 0.1);
    return { value: v, display: v.toFixed(1), min: current.min, max: current.max };
  };

  // Atualiza a cada 5 segundos
  useEffect(() => {
    const id = setInterval(() => {
      setPlant1Indicators(prev => ({
        moisture:    updateMoisture(prev.moisture),
        temperature: updateTemperature(prev.temperature),
        pH:          updatePH(prev.pH),
      }));
      setPlant2Indicators(prev => ({
        moisture:    updateMoisture(prev.moisture),
        temperature: updateTemperature(prev.temperature),
        pH:          updatePH(prev.pH),
      }));
      setPlant3Indicators(prev => ({
        moisture:    updateMoisture(prev.moisture),
        temperature: updateTemperature(prev.temperature),
        pH:          updatePH(prev.pH),
      }));
    }, 5000);
    return () => clearInterval(id);
  }, []);

  // Cálculo para largura da barra
  const calculatePercentage = (value, min, max) =>
    ((value - min) / (max - min)) * 100;

  return (
    <div className="homepage-container">
      <header className="site-header">
        <h1 className="site-title">WebGarden</h1>
        <p className="site-subtitle">Embarcados e Jardinagem</p>
      </header>

      <div className="hero-section" style={{ backgroundImage: `url(${homeImage})` }}>
        <div className="hero-overlay">
          <h2 className="hero-title">Bem-vindo ao WebGarden</h2>
          <p className="hero-description">
            Uma plataforma dedicada à automação inteligente de jardinagem.
          </p>
          <button className="cta-button">Explorar Agora</button>
        </div>
      </div>

      <section className="features-section">
        {/* Planta 1 */}
        <div className="plant-card">
          <div className="plant-image-container">
            <img src={planta1} alt="Planta 1" className="plant-image" />
            {plant1Indicators.moisture.value < 50 && (
              <div className="plant-dry-overlay">
                <img src={plantDRY} alt="Planta ressecada" className="plant-dry-image" />
              </div>
            )}
          </div>
          <div className="plant-content">
            <div className="plant-text">
              <h3 className="plant-title">Planta 1</h3>
              <p className="plant-description">
                Planta ornamental de sombra, perfeita para ambientes internos com pouca luz direta.
              </p>
            </div>
            <div className="plant-indicators">
              <div className="indicator">
                <span className="indicator-label">Umidade</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{ width: `${plant1Indicators.moisture.value}%` }}
                  />
                </div>
                <span className="indicator-value">{plant1Indicators.moisture.display}</span>
              </div>
              <div className="indicator">
                <span className="indicator-label">Temperatura</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{
                      width: `${calculatePercentage(
                        plant1Indicators.temperature.value,
                        plant1Indicators.temperature.min,
                        plant1Indicators.temperature.max
                      )}%`
                    }}
                  />
                </div>
                <span className="indicator-value">{plant1Indicators.temperature.display}</span>
              </div>
              <div className="indicator">
                <span className="indicator-label">pH</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{
                      width: `${calculatePercentage(
                        plant1Indicators.pH.value,
                        plant1Indicators.pH.min,
                        plant1Indicators.pH.max
                      )}%`
                    }}
                  />
                </div>
                <span className="indicator-value">{plant1Indicators.pH.display}</span>
              </div>
            </div>
          </div>
        </div>

        {/* Planta 2 */}
        <div className="plant-card">
          <div className="plant-image-container">
            <img src={planta2} alt="Planta 2" className="plant-image" />
            {plant2Indicators.moisture.value < 50 && (
              <div className="plant-dry-overlay">
                <img src={plantDRY} alt="Planta ressecada" className="plant-dry-image" />
              </div>
            )}
          </div>
          <div className="plant-content">
            <div className="plant-text">
              <h3 className="plant-title">Planta 2</h3>
              <p className="plant-description">
                Vegetal de folha verde, fácil de cultivar.
              </p>
            </div>
            <div className="plant-indicators">
              <div className="indicator">
                <span className="indicator-label">Umidade</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{ width: `${plant2Indicators.moisture.value}%` }}
                  />
                </div>
                <span className="indicator-value">{plant2Indicators.moisture.display}</span>
              </div>
              <div className="indicator">
                <span className="indicator-label">Temperatura</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{
                      width: `${calculatePercentage(
                        plant2Indicators.temperature.value,
                        plant2Indicators.temperature.min,
                        plant2Indicators.temperature.max
                      )}%`
                    }}
                  />
                </div>
                <span className="indicator-value">{plant2Indicators.temperature.display}</span>
              </div>
              <div className="indicator">
                <span className="indicator-label">pH</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{
                      width: `${calculatePercentage(
                        plant2Indicators.pH.value,
                        plant2Indicators.pH.min,
                        plant2Indicators.pH.max
                      )}%`
                    }}
                  />
                </div>
                <span className="indicator-value">{plant2Indicators.pH.display}</span>
              </div>
            </div>
          </div>
        </div>

        {/* Planta 3 */}
        <div className="plant-card">
          <div className="plant-image-container">
            <img src={planta3} alt="Planta 3" className="plant-image" />
            {plant3Indicators.moisture.value < 50 && (
              <div className="plant-dry-overlay">
                <img src={plantDRY} alt="Planta ressecada" className="plant-dry-image" />
              </div>
            )}
          </div>
          <div className="plant-content">
            <div className="plant-text">
              <h3 className="plant-title">Planta 3</h3>
              <p className="plant-description">
                Planta de baixa manutenção, fácil de criar mudas.
              </p>
            </div>
            <div className="plant-indicators">
              <div className="indicator">
                <span className="indicator-label">Umidade</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{ width: `${plant3Indicators.moisture.value}%` }}
                  />
                </div>
                <span className="indicator-value">{plant3Indicators.moisture.display}</span>
              </div>
              <div className="indicator">
                <span className="indicator-label">Temperatura</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{
                      width: `${calculatePercentage(
                        plant3Indicators.temperature.value,
                        plant3Indicators.temperature.min,
                        plant3Indicators.temperature.max
                      )}%`
                    }}
                  />
                </div>
                <span className="indicator-value">{plant3Indicators.temperature.display}</span>
              </div>
              <div className="indicator">
                <span className="indicator-label">pH</span>
                <div className="indicator-bar">
                  <div
                    className="indicator-fill"
                    style={{
                      width: `${calculatePercentage(
                        plant3Indicators.pH.value,
                        plant3Indicators.pH.min,
                        plant3Indicators.pH.max
                      )}%`
                    }}
                  />
                </div>
                <span className="indicator-value">{plant3Indicators.pH.display}</span>
              </div>
            </div>
          </div>
        </div>
      </section>

      <section className="about-section">
        <h2 className="section-title">Sobre Nós</h2>
        <p className="section-description">
          Somos apaixonados por plantas e acreditamos que todos merecem um
          pedacinho de natureza em suas vidas.
        </p>
      </section>

      <footer className="site-footer">
        <p className="footer-text">© 2025 LAWD - Todos os direitos reservados</p>
        <div className="footer-links">
          <a href="#">Contato</a>
          <a href="#">Sobre</a>
          <a href="#">Política de Privacidade</a>
        </div>
      </footer>
    </div>
  );
}

export default HomePage;
